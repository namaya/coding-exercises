
use std::fs;

pub fn day8_treetop_tree_house() {
    let input_path = "inputs/2022/day8/example.txt";
    let input = fs::read_to_string(input_path).unwrap();

    let mut grid: Vec<Vec<u32>> = vec![];

    // convert input to uints
    for row in input.split("\n") {
        grid.push(vec![]);

        for col in row.chars() {
            grid.last_mut().unwrap().push(col.to_digit(10).unwrap());
        }
    }

    // let mut visible_count = 0;
    let mut max_score = 0;

    for i in 0..grid.len() {
        for j in 0..grid[i].len() {
            // if row_visible(&grid, i, j) || col_visible(&grid, i, j) {
            //     visible_count += 1;
            // }
            let score = row_score(&grid, i, j) * col_score(&grid, i, j);

            // println!("{}, {}: {}", i, j, score);

            if score > max_score {
                max_score = score;
            }
        }
    }

    // println!("{}", visible_count);
    println!("{}", max_score);
}

fn row_score(grid: &Vec<Vec<u32>>, i: usize, j: usize) -> u32 {
    let mut score = 1;
    let mut block_k = 0usize;

    for k in (0..j).rev() {
        if grid[i][k] >= grid[i][j] {
            block_k = k;
            break;
        }
    }

    score *= j.abs_diff(block_k) as u32;

    block_k = grid[i].len()-1;

    for k in j+1..grid[i].len() {
        if grid[i][k] >= grid[i][j] {
            block_k = k;
            break;
        }
    }

    score *= j.abs_diff(block_k) as u32;

    score
}

fn col_score(grid: &Vec<Vec<u32>>, i: usize, j: usize) -> u32 {
    let mut score = 1;
    let mut block_k = 0usize;

    for k in (0..i).rev() {
        if grid[k][j] >= grid[i][j] {
            block_k = k;
            break;
        }
    }

    score *= i.abs_diff(block_k) as u32;

    block_k = grid.len()-1;

    for k in i+1..grid.len() {
        if grid[i][k] >= grid[i][j] {
            block_k = k;
            break;
        }
    }

    score *= i.abs_diff(block_k) as u32;

    score
}


fn row_visible(grid: &Vec<Vec<u32>>, i: usize, j: usize) -> bool {
    let mut is_visible = true;

    for k in 0..j {
        if grid[i][k] >= grid[i][j] {
            is_visible = false;
            break;
        }
    }

    if is_visible {
        return true;
    }

    is_visible = true;

    for k in j+1..grid[i].len() {
        if grid[i][k] >= grid[i][j] {
            is_visible = false;
            break;
        }
    }

    is_visible
}

fn col_visible(grid: &Vec<Vec<u32>>, i: usize, j: usize) -> bool {
    let mut is_visible = true;

    for k in 0..i {
        if grid[k][j] >= grid[i][j] {
            is_visible = false;
            break;
        }
    }

    if is_visible {
        return true;
    }

    is_visible = true;

    for k in i+1..grid.len() {
        if grid[k][j] >= grid[i][j] {
            is_visible = false;
            break;
        }
    }

    is_visible
}