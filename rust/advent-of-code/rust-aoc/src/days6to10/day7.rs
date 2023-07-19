
use std::cmp::PartialEq;
use std::fs;
use std::iter::Peekable;
use std::str::Split;

use crate::days1to5::day2_rock_paper_scissors;


#[derive(Debug)]
struct File {
    name: String,
    size: u32,
    parent: Option<usize>,
    is_dir: bool,
}

impl PartialEq for File {
    fn eq(&self, other: &Self) -> bool {
        self.name == other.name && self.parent == other.parent
    }
}

struct FileSystem {
    root: usize,
    work_dir: usize,
    files: Vec<File>
}

impl FileSystem {
    fn new() -> FileSystem {
        FileSystem { 
            root: 0,
            work_dir: 0,
            files: vec![
                File {
                    name: String::from("/"),
                    size: 0,
                    parent: None,
                    is_dir: true
                }
            ],
        }
    }

    fn pwd(&self) -> &File {
        &self.files[self.work_dir]
    }

    fn cd(&mut self, new_dir: &str) {
        let old_dir = self.work_dir;

        let work_dir = match new_dir {
            "/" => self.root,
            ".." => self.pwd().parent
                .expect("trying to cd above the root dir."),
            dir => {
                if let Some(index) = self.files.iter()
                    .position(|file| file.name == dir && file.parent == Some(self.work_dir))
                {
                    index
                } else {
                    let new_file = File { name: String::from(dir), size: 0, parent: Some(self.work_dir), is_dir: true };

                    println!("Adding new file {} with size {} to {}", new_file.name, new_file.size, self.pwd().name);

                    self.files.push(new_file);
                    self.files.len() - 1
                }
            }
        };

        println!("cd to {} from {}", self.files[work_dir].name, self.files[old_dir].name);

        self.work_dir = work_dir;
    }

    fn ls(&mut self, commands_iter: &mut Peekable<Split<&str>>) {
        println!("ls {}", self.pwd().name);

        while commands_iter.peek().is_some_and(|command| !command.starts_with("$")) {
            let ls_line_output = commands_iter.next().unwrap();
            let ls_line_output = ls_line_output.split_whitespace().collect::<Vec<&str>>();

            let new_file = match ls_line_output[0] {
                "dir" => File {
                    name: String::from(ls_line_output[1]),
                    size: 0,
                    parent: Some(self.work_dir),
                    is_dir: true,
                },
                size => File {
                    name: String::from(ls_line_output[1]),
                    size: size.parse::<u32>().expect("size is not a integer."),
                    parent: Some(self.work_dir),
                    is_dir: false,
                }
            };

            if let None = self.files.iter()
                .position(|file| file.name == new_file.name && file.parent == new_file.parent)
            {
                println!("Adding new file {} with size {} to {}", new_file.name, new_file.size, self.pwd().name);

                let mut cur_dir = Some(self.work_dir);

                while cur_dir.is_some() {
                    let cur_dir_file = &mut self.files[cur_dir.unwrap()];

                    cur_dir_file.size += new_file.size;
                    cur_dir = cur_dir_file.parent;
                }

                self.files.push(new_file);
            }
        }
    }

    fn dirs_sum(&self) -> u32 {
        let DIR_SIZE = 100_000;

        self.files.iter()
            .filter(|file| file.is_dir && file.size <= DIR_SIZE)
            .map(|file| file.size)
            .sum()
    }
}

pub fn day7_no_space_left_on_device() {
    let input_path = "inputs/2022/day7/full.txt";

    let mut fs = FileSystem::new();

    let commands = fs::read_to_string(input_path)
                                .expect(&format!("issue opening file {input_path}"));

    let mut commands_iter = commands.split("\n").peekable();

    let mut command_option = commands_iter.next();
    
    while command_option.is_some() {
        let command = command_option.unwrap()
            .strip_prefix("$")
            .expect("malformed command");


        let tokens: Vec<&str> = command.split_whitespace().collect();

        match tokens[0] {
            "cd" => fs.cd(tokens[1]),
            "ls" => fs.ls(&mut commands_iter),
            cmd => panic!("unknown command {cmd}")
        }

        command_option = commands_iter.next();
    }

    println!("{}", fs.dirs_sum());

    // println!("{:?}", fs.files);
}
