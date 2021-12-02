use std::env;
use tokio::fs;
use chrono::prelude::*;
use dotenv::dotenv;
use reqwest::Client;
use reqwest::StatusCode;

async fn fetch(path: String, d: u32, y: i32) -> Result<(), reqwest::Error> {
    let session = match env::var("SESSION") {
        Ok(x) => x,
        Err(_) => panic!("Please define a SESSION variable"),
    };

    let response = Client::new()
        .get(format!("https://adventofcode.com/{}/day/{}/input", y, d))
        .header("Cookie", format!("session={}", session))
        .send()
        .await?;

    match response.status() {
        StatusCode::OK => println!("Successfully downloaded input for Day {} ({})", d, y),
        s => panic!("Received response status: {:?}", s),
    }

    let text = response.text().await?;

    fs::create_dir_all(&path).await;
    fs::write(format!("{}/input.txt", &path), text).await;

    Ok(())
}

#[tokio::main]
async fn main() {
    dotenv().ok();

    let args: Vec<String> = env::args().collect();
    let dt = Local::now();

    let d = match args.get(1) {
        Some(x) => x.parse::<u32>().unwrap(),
        None => dt.day()
    };

    let y = match args.get(2) {
        Some(x) => x.parse::<i32>().unwrap(),
        None => dt.year()
    };

    let path = format!("../inputs/{}/{}", y, d);

    let file_exists = fs::metadata(&path).await;

    match file_exists {
        Ok(_) => println!("Input for Day {} ({}) already downloaded", d, y),
        Err(_) => fetch(path, d, y).await.expect("Failed to download input")
    }
}