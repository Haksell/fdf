mod canvas;
mod color;
mod height_map;

use {
    canvas::Canvas,
    clap::Parser,
    height_map::HeightMap,
    minifb::{Key, Window, WindowOptions},
};

const WIDTH: usize = 800;
const HEIGHT: usize = 800;

#[derive(Parser, Debug)]
#[command(name = "TODO")]
#[command(about = "TODO", long_about = None)]
struct Args {
    #[arg(value_parser = validate_fdf)]
    path: String,
}

fn validate_fdf(s: &str) -> Result<String, String> {
    if s.ends_with(".fdf") {
        Ok(s.to_string())
    } else {
        Err("Filename must have a .fdf extension".into())
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Args::parse();
    println!("Parsing file {}", args.path);
    let height_map = HeightMap::parse(&args.path)?;

    println!("{height_map:?}");

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

    Ok(())
}
