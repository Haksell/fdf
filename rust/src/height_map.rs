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

enum MapParseError {
    // ...
}

impl HeightMap {
    pub fn parse(path: &str) -> Result<Self, MapParseError> {
        todo!()
    }

    pub fn get(&self, x: usize, y: usize) -> VertexData {
        assert!(x < self.width);
        assert!(y < self.height);
        self.data[y * self.width + x]
    }
}
