mod canvas;
mod color;

use {
    canvas::Canvas,
    minifb::{Key, Window, WindowOptions},
};

const WIDTH: usize = 800;
const HEIGHT: usize = 800;

fn main() {
    let canvas = Canvas::new(WIDTH, HEIGHT);

    let mut window = Window::new("rt", canvas.width, canvas.height, WindowOptions::default())
        .unwrap_or_else(|e| panic!("{}", e));
    window.set_target_fps(60);

    let mut buffer: Vec<u32> = vec![0; canvas.width * canvas.height];
    while window.is_open() && !window.is_key_down(Key::Escape) {
        for (i, pixel) in buffer.iter_mut().enumerate() {
            *pixel = canvas
                .get_pixel(i % canvas.width, i / canvas.width)
                .to_u32();
        }
        window
            .update_with_buffer(&buffer, canvas.width, canvas.height)
            .unwrap();
    }
}
