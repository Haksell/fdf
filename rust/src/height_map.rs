use std::{
    fmt,
    fs::File,
    io::{BufRead, BufReader},
};

const MINIMUM_DIMENSION: usize = 2;

#[derive(Debug)]
pub enum MapParseError {
    IoError(std::io::Error),
    ParseHeight(String),
    ParseColor(String),
    NotRectangular { expected: usize, found: usize },
    Empty,
    TooSmall,
}

impl From<std::io::Error> for MapParseError {
    fn from(err: std::io::Error) -> Self {
        MapParseError::IoError(err)
    }
}

impl fmt::Display for MapParseError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            MapParseError::IoError(e) => write!(f, "IO error: {}", e),
            MapParseError::ParseHeight(e) => write!(f, "Height parse error: {}", e),
            MapParseError::ParseColor(e) => write!(f, "Color parse error: {}", e),
            MapParseError::NotRectangular { expected, found } => {
                write!(f, "Expected {} columns, found {}", expected, found)
            }
            MapParseError::Empty => write!(f, "Map is empty"),
            MapParseError::TooSmall => write!(
                f,
                "Map is too small (should be at least {}x{}",
                MINIMUM_DIMENSION, MINIMUM_DIMENSION
            ),
        }
    }
}

impl std::error::Error for MapParseError {}

#[derive(Clone, Copy, Debug)]
pub struct VertexData {
    height: f32,
    color: u32,
}

impl VertexData {
    pub fn parse(token: &str) -> Result<Self, MapParseError> {
        if let Some((height_str, color_str)) = token.split_once(',') {
            let height: f32 = height_str
                .parse()
                .map_err(|_| MapParseError::ParseHeight(height_str.into()))?;

            if !color_str.starts_with("0x") {
                return Err(MapParseError::ParseColor(color_str.into()));
            }
            let color = u32::from_str_radix(&color_str[2..], 16)
                .map_err(|_| MapParseError::ParseColor(color_str.into()))?;
            if color > 0xffffff {
                return Err(MapParseError::ParseColor(color_str.into()));
            }

            Ok(VertexData { height, color })
        } else {
            let height: f32 = token
                .parse()
                .map_err(|_| MapParseError::ParseHeight(token.into()))?;

            Ok(VertexData { height, color: !0 })
        }
    }
}

#[derive(Debug)]
pub struct HeightMap {
    pub width: usize,
    pub height: usize,
    data: Vec<VertexData>,
}

impl HeightMap {
    pub fn parse(path: &str) -> Result<Self, MapParseError> {
        let file = File::open(path)?;
        let reader = BufReader::new(file);

        let mut data = Vec::new();
        let (mut width, mut height) = (0, 0);

        for line_res in reader.lines() {
            let line = line_res?;
            let tokens: Vec<&str> = line.trim().split_whitespace().collect();

            if tokens.is_empty() {
                continue;
            }

            if height == 0 {
                width = tokens.len();
                if width < MINIMUM_DIMENSION {
                    return Err(MapParseError::TooSmall);
                }
            } else if tokens.len() != width {
                return Err(MapParseError::NotRectangular {
                    expected: width,
                    found: tokens.len(),
                });
            }

            for token in tokens {
                data.push(VertexData::parse(token)?);
            }

            height += 1;
        }

        if height == 0 {
            return Err(MapParseError::Empty);
        } else if height < MINIMUM_DIMENSION {
            return Err(MapParseError::TooSmall);
        }

        data.shrink_to_fit();

        Ok(HeightMap {
            width,
            height,
            data,
        })
    }

    pub fn _get(&self, x: usize, y: usize) -> VertexData {
        assert!(x < self.width);
        assert!(y < self.height);
        self.data[y * self.width + x]
    }
}

#[cfg(test)]
mod tests {
    use {
        super::*,
        std::{
            fs::{self, Permissions},
            os::unix::fs::PermissionsExt,
            path::Path,
        },
    };

    struct PermissionGuard<'a> {
        path: &'a Path,
        original: Permissions,
    }

    impl<'a> PermissionGuard<'a> {
        fn new(path: &'a Path, mode: u32) -> Self {
            let original = fs::metadata(path)
                .expect("Failed to get metadata")
                .permissions();

            fs::set_permissions(path, Permissions::from_mode(mode))
                .expect("Failed to change permissions");

            Self { path, original }
        }
    }

    impl Drop for PermissionGuard<'_> {
        fn drop(&mut self) {
            let _ = fs::set_permissions(self.path, self.original.clone());
        }
    }

    #[test]
    fn test_valid_maps() {
        for entry in fs::read_dir("../maps/valid").expect("Reading valid directory failed") {
            let path = entry.expect("Invalid entry").path();
            let result = HeightMap::parse(path.to_str().unwrap());
            assert!(
                result.is_ok(),
                "Expected Ok for valid file: {:?}, got Err: {:?}",
                path,
                result.err()
            );
        }
    }

    #[test]
    fn test_invalid_maps() {
        for entry in fs::read_dir("../maps/invalid").expect("Reading invalid directory failed") {
            let path = entry.expect("Invalid entry").path();

            let _guard = path
                .ends_with("unreadable.fdf")
                .then(|| PermissionGuard::new(&path, 0));

            let result = HeightMap::parse(path.to_str().unwrap());
            assert!(
                result.is_err(),
                "Expected Err for invalid file: {:?}, got Ok",
                path
            );
        }
    }
}
