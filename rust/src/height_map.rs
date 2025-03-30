use std::{
    fmt,
    fs::File,
    io::{BufRead, BufReader},
    num::{ParseFloatError, ParseIntError},
};

#[derive(Debug)]
pub enum MapParseError {
    IoError(std::io::Error),
    ParseHeight(ParseFloatError),
    ParseColor(ParseIntError),
    NotRectangular { expected: usize, found: usize },
    Empty,
}

impl From<std::io::Error> for MapParseError {
    fn from(err: std::io::Error) -> Self {
        MapParseError::IoError(err)
    }
}

impl From<ParseFloatError> for MapParseError {
    fn from(err: ParseFloatError) -> Self {
        MapParseError::ParseHeight(err)
    }
}

impl From<ParseIntError> for MapParseError {
    fn from(err: ParseIntError) -> Self {
        MapParseError::ParseColor(err)
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
        Ok(
            if let Some((height_str, color_str)) = token.split_once(',') {
                let height: f32 = height_str.parse()?;
                let color: u32 = u32::from_str_radix(color_str.trim_start_matches("0x"), 16)?;
                VertexData { height, color }
            } else {
                let height: f32 = token.parse()?;
                VertexData { height, color: !0 }
            },
        )
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
