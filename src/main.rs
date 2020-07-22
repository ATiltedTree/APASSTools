use iced::{button, Application, Button, Column, Element, Settings, Text};

fn main() {
    State::run(Settings::default())
}

#[derive(Default, Debug)]
struct State {
    button: button::State,
}

#[derive(Debug, Clone)]
enum Message {
    Loaded(),
    Saved(),
    InputChanged(String),
}

impl Application for State {
    type Executor = iced::executor::Default;
    type Message = Message;
    type Flags = ();
    fn new(flags: Self::Flags) -> (Self, iced::Command<Self::Message>) {
        (State::default(), iced::Command::none())
    }
    fn title(&self) -> String {
        "APASSTools".to_string()
    }
    fn update(&mut self, message: Self::Message) -> iced::Command<Self::Message> {
        iced::Command::none()
    }
    fn view(&mut self) -> Element<'_, Self::Message> {
        Column::new()
            .push(Button::new(&mut self.button, Text::new("label")))
            .into()
    }
}
