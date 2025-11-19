use std::collections::LinkedList;
use std::fs;

struct Monkey {
    items: LinkedList<i32>,
    operation: Box<dyn Fn(i32) -> i32>,
    divisible_by: u32,
    true_monkey: usize,
    false_monkey: usize,
}

impl Monkey {
    fn new(
        items: impl Iterator<Item = i32>,
        operation: Box<dyn Fn(i32) -> i32>,
        divisible_by: u32,
        true_monkey: usize,
        false_monkey: usize,
    ) -> Monkey {
        Monkey {
            items: LinkedList::from_iter(items),
            operation,
            divisible_by,
            true_monkey,
            false_monkey,
        }
    }

    fn inspect_next_item(&mut self) -> Option<(i32, usize)> {
        let item = self.items.pop_front();

        if let None = item {
            return None;
        }

        let item = item.unwrap();

        let item = self.operation.as_ref()(item);
        let item = item / 3;

        Some((item, self.throw(item)))
    }

    fn throw(&self, item: i32) -> usize {
        if item % (self.divisible_by as i32) == 0 {
            self.true_monkey
        } else {
            self.false_monkey
        }
    }

    fn give(&mut self, item: i32) {
        self.items.push_back(item);
    }
}

struct MonkeyTroop {
    monkeys: Vec<Monkey>,
}

impl MonkeyTroop {
    fn new(monkeys: Vec<Monkey>) -> MonkeyTroop {
        MonkeyTroop { monkeys }
    }

    fn play_round(&mut self) {
        for i in 0..self.monkeys.len() {
            let mut res = self.monkeys[i].inspect_next_item();
            while res.is_some() {
                let (item, new_monkey) = res.unwrap();

                self.monkeys[new_monkey].give(item);

                res = self.monkeys[i].inspect_next_item();
            }
        }
    }
}

pub fn monkey_in_the_middle_p1() {
    let n_rounds = 20;

    let input_path = "inputs/2022/day11/example.txt";

    let input = fs::read_to_string(input_path).expect("Couldn't read file.");

    let mut monkeys: Vec<Monkey> = Vec::new();

    for monkey_text in input.split("\n\n") {
        let monkey_lines = monkey_text.lines().collect::<Vec<&str>>();

        let items = monkey_lines[1].split(":").collect::<Vec<&str>>()[1]
            .split(",")
            .map(|item_txt| item_txt.parse::<i32>().expect("invalid worry level."));

        let operation_str = monkey_lines[2].split(":").collect::<Vec<&str>>()[1]
            .split("=")
            .collect::<Vec<&str>>()[1];

        let tokens = operation_str.split_whitespace().collect::<Vec<&str>>();

        let operation: Box<dyn Fn(i32) -> i32> = match tokens[1] {
            "+" => match tokens[2] {
                "old" => Box::new(|old: i32| old + old),
                num => Box::new(|old: i32| {
                    old + num.parse::<i32>().expect("invalid arg to '+' operator.")
                }),
            },
            "*" => match tokens[2] {
                "old" => Box::new(|old: i32| old * old),
                num => Box::new(|old: i32| {
                    old * num.parse::<i32>().expect("invalid arg to '+' operator.")
                }),
            },
            op => panic!("unknown operator {op}"),
        };

        let divisible_by = monkey_lines[3]
            .split_whitespace()
            .last()
            .expect("invalid test format.")
            .parse::<u32>()
            .expect("invalid test format.");

        let true_monkey = monkey_lines[4]
            .split_whitespace()
            .last()
            .expect("invalid test format.")
            .parse::<usize>()
            .expect("invalid test format.");

        let false_monkey = monkey_lines[4]
            .split_whitespace()
            .last()
            .expect("invalid test format.")
            .parse::<usize>()
            .expect("invalid test format.");

        monkeys.push(Monkey::new(
            items,
            operation,
            divisible_by,
            true_monkey,
            false_monkey,
        ));
    }

    let mut troop = MonkeyTroop::new(monkeys);

    for _ in 0..n_rounds {
        troop.play_round();
    }
}
