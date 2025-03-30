use std::fs::File;
use std::io::{BufRead, BufReader};
use std::num::ParseFloatError;
use std::num::ParseIntError;

#[derive(Clone, Copy, Debug)]
pub struct VertexData {
    height: f32,
    color: u32,
}

#[derive(Debug)]
pub struct HeightMap {
    pub width: usize,
    pub height: usize,
    data: Vec<VertexData>,
}

#[derive(Debug)]
pub enum MapParseError {
    IoError(std::io::Error),
    InvalidFormat(String),
    ParseHeight(ParseFloatError),
    ParseColor(ParseIntError),
    NotRectangular(usize, usize), // (expected, found)
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

impl HeightMap {
    pub fn parse(path: &str) -> Result<Self, MapParseError> {
        let file = File::open(path)?;
        let reader = BufReader::new(file);

        let mut data = Vec::new();
        let mut width = None;
        let mut height = 0;

        for line_res in reader.lines() {
            let line = line_res?;
            let tokens: Vec<&str> = line.trim().split_whitespace().collect();

            if let Some(expected_width) = width {
                if tokens.len() != expected_width {
                    return Err(MapParseError::NotRectangular(expected_width, tokens.len()));
                }
            } else {
                width = Some(tokens.len());
            }

            for token in tokens {
                let vertex = if let Some((height_str, color_str)) = token.split_once(',') {
                    let height: f32 = height_str.parse()?;
                    let color: u32 = u32::from_str_radix(color_str.trim_start_matches("0x"), 16)?;
                    VertexData { height, color }
                } else {
                    let height: f32 = token.parse()?;
                    VertexData { height, color: !0 }
                };
                data.push(vertex);
            }

            height += 1;
        }

        let width = width.ok_or(MapParseError::Empty)?;

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
