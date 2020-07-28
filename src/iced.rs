use iced::{
    button, text_input, Application, Button, Column, Element, Row, Settings, Text, TextInput,
};

fn main() {
    State::run(Settings::default())
}

#[derive(Default, Debug)]
struct State {
    load_button: button::State,
    save_button: button::State,

    name_state: text_input::State,
    name: String,
}


#[derive(Debug, Clone)]
enum Message {
    Load,
    Save,
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
        match message {
            Message::Load => println!("LOAD: {}", self.name),
            Message::Save => println!("SAVE: {}", self.name),
            Message::InputChanged(s) => self.name = s,
        };

        iced::Command::none()
    }
    fn view(&mut self) -> Element<'_, Self::Message> {
        Column::new()
            .push(
                Row::new()
                    .push(
                        Button::new(&mut self.load_button, Text::new("Load"))
                            .on_press(Message::Load),
                    )
                    .push(
                        Button::new(&mut self.save_button, Text::new("Save"))
                            .on_press(Message::Save),
                    ),
            )
            .push(Row::new().push(Text::new("Name")).push(TextInput::new(
                &mut self.name_state,
                "name",
                self.name.as_str(),
                |s| Message::InputChanged(s),
            )))
            .push(Row::new().push(Text::new("Observation Threshhold")))
            .push(Row::new().push(Text::new("Magnitude Threshhold")))
            .into()
    }
}
