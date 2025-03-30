#[derive(Default, Debug, PartialEq, Clone, Copy)]
pub struct Color {
    pub r: f64,
    pub g: f64,
    pub b: f64,
}

impl Color {
    pub fn black() -> Self {
        Self {
            r: 0.0,
            g: 0.0,
            b: 0.0,
        }
    }

    pub fn to_u32(&self) -> u32 {
        let r = (self.r.clamp(0., 1.) * 255.).round() as u32;
        let g = (self.g.clamp(0., 1.) * 255.).round() as u32;
        let b = (self.b.clamp(0., 1.) * 255.).round() as u32;
        (r << 16) | (g << 8) | b
    }
}
