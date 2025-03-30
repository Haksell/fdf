use crate::color::Color;

// TODO: maybe don't go through all of this and write in buffer directly

#[derive(Debug, PartialEq)]
pub struct Canvas {
    pub width: usize,
    pub height: usize,
    pixels: Vec<Vec<Color>>, // TODO: just Vec<Color>?
}

impl Canvas {
    pub fn new(width: usize, height: usize) -> Self {
        let pixels = vec![vec![Color::black(); width]; height];
        Canvas {
            width,
            height,
            pixels,
        }
    }

    pub fn _set_pixel(&mut self, x: usize, y: usize, c: Color) {
        assert!(x < self.width);
        assert!(y < self.height);
        self.pixels[y][x] = c;
    }

    pub fn get_pixel(&self, x: usize, y: usize) -> Color {
        assert!(x < self.width);
        assert!(y < self.height);
        self.pixels[y][x]
    }
}
