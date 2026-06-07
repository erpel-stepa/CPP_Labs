#include "module.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>

const int kMinHeight = 50;
const int kMaxHeight = 250;
const int kMinCost = 1;
const int kMaxCost = 1000;

const std::vector<std::string> kRandomSurnames = {
    "Иванов", "Петров", "Сидоров", "Пушкин", "Маяковский",
    "Смирнов", "Волков", "Орлов", "Кузнецов", "Лебедев"};

const std::vector<std::string> kRandomGivenNames = {
    "Иван", "Петр", "Александр", "Владимир", "Лев",
    "Сергей", "Борис", "Клеопатра", "Анна", "Олег"};

const std::vector<std::string> kRandomPatronymics = {
    "Иванович", "Петрович", "Александрович", "Сергеевич",
    "Владимирович", "Олегович", "Львович", "Борисович"};

const std::vector<std::string> kRandomCities = {
    "A", "B", "C", "D", "E", "F", "G", "H"};

// ==================== Name ====================

Name::Name() = default;

Name::Name(const std::string& given_name) {
  set_given_name(given_name);
}

Name::Name(const std::string& given_name, const std::string& surname) {
  set_given_name(given_name);
  set_surname(surname);
}

Name::Name(const std::string& given_name,
           const std::string& surname,
           const std::string& patronymic) {
  set_given_name(given_name);
  set_surname(surname);
  set_patronymic(patronymic);
}

Name::Name(const Name& other)
    : surname_(other.surname_),
      given_name_(other.given_name_),
      patronymic_(other.patronymic_) {}

Name& Name::operator=(const Name& other) {
  if (this != &other) {
    surname_ = other.surname_;
    given_name_ = other.given_name_;
    patronymic_ = other.patronymic_;
  }
  return *this;
}

const std::string& Name::surname() const {
  return surname_;
}

const std::string& Name::given_name() const {
  return given_name_;
}

const std::string& Name::patronymic() const {
  return patronymic_;
}

void Name::set_surname(const std::string& surname) {
  if (surname.empty()) {
    surname_.clear();
    return;
  }
  surname_ = surname;
}

void Name::set_given_name(const std::string& given_name) {
  if (given_name.empty()) {
    given_name_.clear();
    return;
  }
  given_name_ = given_name;
}

void Name::set_patronymic(const std::string& patronymic) {
  if (patronymic.empty()) {
    patronymic_.clear();
    return;
  }
  patronymic_ = patronymic;
}

bool Name::has_surname() const {
  return !surname_.empty();
}

bool Name::has_given_name() const {
  return !given_name_.empty();
}

bool Name::has_patronymic() const {
  return !patronymic_.empty();
}

std::string Name::to_string() const {
  std::string result;

  if (!surname_.empty()) {
    result += surname_;
  }

  if (!given_name_.empty()) {
    if (!result.empty()) {
      result += " ";
    }
    result += given_name_;
  }

  if (!patronymic_.empty()) {
    if (!result.empty()) {
      result += " ";
    }
    result += patronymic_;
  }

  return result;
}

void Name::print() const {
  std::cout << to_string() << '\n';
}

bool is_empty_name(const Name& name) {
  return !name.has_surname() &&
         !name.has_given_name() &&
         !name.has_patronymic();
}

// ==================== Person ====================

Person::Person()
    : name_(), height_(170), father_(nullptr) {}

Person::Person(const std::string& given_name, int height)
    : name_(given_name), height_(170), father_(nullptr) {
  set_height(height);
}

Person::Person(const std::string& given_name, int height, Person* father)
    : name_(given_name), height_(170), father_(father) {
  set_height(height);
  fill_name_from_father();
}

Person::Person(const Name& name, int height)
    : name_(name), height_(170), father_(nullptr) {
  set_height(height);
}

Person::Person(const Name& name, int height, Person* father)
    : name_(name), height_(170), father_(father) {
  set_height(height);
  fill_name_from_father();
}

Person::Person(const Person& other)
    : name_(other.name_),
      height_(other.height_),
      father_(other.father_) {}

Person& Person::operator=(const Person& other) {
  if (this != &other) {
    name_ = other.name_;
    height_ = other.height_;
    father_ = other.father_;
  }
  return *this;
}

const Name& Person::name() const {
  return name_;
}

int Person::height() const {
  return height_;
}

Person* Person::father() const {
  return father_;
}

void Person::set_name(const Name& name) {
  name_ = name;
}

void Person::set_height(int height) {
  if (height < kMinHeight || height > kMaxHeight) {
    height_ = 170;
    return;
  }
  height_ = height;
}

void Person::set_father(Person* father) {
  father_ = father;
  fill_name_from_father();
}

void Person::fill_name_from_father() {
  if (father_ == nullptr) {
    return;
  }

  if (!name_.has_surname() && father_->name().has_surname()) {
    name_.set_surname(father_->name().surname());
  }

  if (!name_.has_patronymic() && father_->name().has_given_name()) {
    name_.set_patronymic(father_->name().given_name() + "ович");
  }
}

std::string Person::to_string() const {
  return name_.to_string() + ", рост " + std::to_string(height_);
}

void Person::print() const {
  std::cout << to_string() << '\n';
}

// ==================== City ====================

City::City() : name_("Unknown") {}

City::City(const std::string& name) : name_("Unknown") {
  set_name(name);
}

City::City(const std::string& name,
           const std::vector<std::pair<std::string, int>>& routes)
    : name_("Unknown"), routes_(routes) {
  set_name(name);
}

City::City(const City& other)
    : name_(other.name_),
      routes_(other.routes_) {}

City& City::operator=(const City& other) {
  if (this != &other) {
    name_ = other.name_;
    routes_ = other.routes_;
  }
  return *this;
}

const std::string& City::name() const {
  return name_;
}

const std::vector<std::pair<std::string, int>>& City::routes() const {
  return routes_;
}

void City::set_name(const std::string& name) {
  if (!name.empty()) {
    name_ = name;
  }
}

void City::add_route(const std::string& to_city, int cost) {
  routes_.push_back(std::make_pair(to_city, cost));
}

void City::clear_routes() {
  routes_.clear();
}

std::string City::to_string() const {
  std::string result = name_ + ": ";

  if (routes_.empty()) {
    result += "нет путей";
    return result;
  }

  for (std::size_t i = 0; i < routes_.size(); ++i) {
    result += routes_[i].first + ":" + std::to_string(routes_[i].second);
    if (i + 1 != routes_.size()) {
      result += ", ";
    }
  }

  return result;
}

void City::print() const {
  std::cout << to_string();
}

// ==================== Cat ====================

Cat::Cat() = default;

Cat::Cat(const std::string& name) {
  set_name(name);
}

Cat::Cat(const Cat& other) : name_(other.name_) {}

Cat& Cat::operator=(const Cat& other) {
  if (this != &other) {
    name_ = other.name_;
  }
  return *this;
}

const std::string& Cat::name() const {
  return name_;
}

void Cat::set_name(const std::string& name) {
  if (!name.empty()) {
    name_ = name;
  }
}

std::string Cat::to_string() const {
  return "кот: " + name_;
}

void Cat::print() const {
  std::cout << to_string() << '\n';
}

void Cat::meow() const {
  std::cout << name_ << ": мяу!\n";
}

void Cat::meow(int count) const {
  std::cout << name_ << ": ";
  for (int i = 0; i < count; ++i) {
    std::cout << "мяу";
    if (i + 1 != count) {
      std::cout << "-";
    }
  }
  std::cout << "!\n";
}

// ==================== Проверки ====================

bool is_valid_word(const std::string& text) {
  if (text.empty()) {
    return false;
  }

  for (std::size_t i = 0; i < text.size(); ++i) {
    const unsigned char ch = static_cast<unsigned char>(text[i]);
    if (std::isalpha(ch) == 0 && ch != '-') {
      if (ch < 128) {
        return false;
      }
    }
  }

  return true;
}

bool is_valid_phrase(const std::string& text) {
  if (text.empty()) {
    return false;
  }

  for (std::size_t i = 0; i < text.size(); ++i) {
    const unsigned char ch = static_cast<unsigned char>(text[i]);
    if (std::isalpha(ch) == 0 && ch != '-' && ch != ' ') {
      if (ch < 128) {
        return false;
      }
    }
  }

  return true;
}

// ==================== Ввод ====================

std::string read_non_empty_line(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);

    if (value.empty()) {
      std::cout << "Ошибка: пустой ввод\n";
      continue;
    }

    return value;
  }
}

std::string read_word(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);
    if (!is_valid_word(value)) {
      std::cout << "Ошибка: вводите слово\n";
      continue;
    }
    return value;
  }
}

std::string read_phrase(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);
    if (!is_valid_phrase(value)) {
      std::cout << "Ошибка: некорректная строка\n";
      continue;
    }
    return value;
  }
}

std::string read_optional_word(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);

    if (value == "-" || value == "0") {
      return "";
    }

    if (!is_valid_word(value)) {
      std::cout << "Ошибка: введите слово, или - если нет\n";
      continue;
    }

    return value;
  }
}

int read_int(const std::string& prompt, int min_value, int max_value) {
  while (true) {
    std::cout << prompt;

    int value = 0;
    if (!(std::cin >> value)) {
      std::cout << "Ошибка: введите целое число\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (value < min_value || value > max_value) {
      std::cout << "Ошибка: число вне диапазона ["
                << min_value << ", " << max_value << "]\n";
      continue;
    }

    return value;
  }
}

int read_mode_choice() {
  std::cout << "\n1. Ввод с клавиатуры\n";
  std::cout << "2. Случайная генерация\n";
  std::cout << "3. Ввод из файла\n";
  return read_int("Выберите способ ввода: ", 1, 3);
}

std::string read_file_path() {
  return read_non_empty_line("Введите путь к файлу: ");
}

std::ifstream open_input_file_with_retry() {
  while (true) {
    const std::string path = read_file_path();
    std::ifstream file(path);

    if (!file.is_open()) {
      std::cout << "Ошибка: не удалось открыть файл\n";
      continue;
    }

    return file;
  }
}

// ==================== Случайные данные ====================

int random_int(int min_value, int max_value) {
  static bool initialized = false;
  if (!initialized) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initialized = true;
  }

  return min_value + std::rand() % (max_value - min_value + 1);
}

std::string random_word(const std::vector<std::string>& values) {
  if (values.empty()) {
    return "";
  }

  const int index = random_int(0, static_cast<int>(values.size()) - 1);
  return values[static_cast<std::size_t>(index)];
}

// ==================== Файл и режимы ====================

std::string read_word_from_file(std::ifstream& file) {
  std::string value;
  if (!(file >> value)) {
    return "";
  }
  return value;
}

std::string get_word_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    const std::vector<std::string>& random_values) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_word(prompt);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const std::string value = random_word(random_values);
    std::cout << prompt << value << '\n';
    return value;
  }

  const std::string value = read_word_from_file(file);
  if (value.empty()) {
    const std::string fallback = random_word(random_values);
    std::cout << "Ошибка: в файле не хватает слов\n";
    std::cout << prompt << fallback << '\n';
    return fallback;
  }
  if (!is_valid_word(value)) {
    const std::string fallback = random_word(random_values);
    std::cout << "Ошибка: некорректное слово в файле\n";
    std::cout << prompt << fallback << '\n';
    return fallback;
  }

  std::cout << prompt << value << '\n';
  return value;
}

std::string get_optional_word_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    const std::vector<std::string>& random_values) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_optional_word(prompt);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const int roll = random_int(1, 100);
    if (roll <= 20) {
      std::cout << prompt << "-" << '\n';
      return "";
    }

    const std::string value = random_word(random_values);
    std::cout << prompt << value << '\n';
    return value;
  }

  const std::string value = read_word_from_file(file);
  if (value.empty()) {
    std::cout << prompt << "-" << '\n';
    return "";
  }

  std::cout << prompt << value << '\n';

  if (value == "-" || value == "0") {
    return "";
  }

  if (!is_valid_word(value)) {
    std::cout << "Ошибка: некорректный атрибут в файле\n";
    return "";
  }

  return value;
}

int get_int_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    int min_value,
    int max_value) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_int(prompt, min_value, max_value);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const int value = random_int(min_value, max_value);
    std::cout << prompt << value << '\n';
    return value;
  }

  int value = 0;
  if (!(file >> value)) {
    std::cout << "Ошибка: не хватает чисел в файле\n";
    std::cout << prompt << min_value << '\n';
    return min_value;
  }

  if (value < min_value || value > max_value) {
    std::cout << "Ошибка: число в файле вне диапазона\n";
    std::cout << prompt << min_value << '\n';
    return min_value;
  }

  std::cout << prompt << value << '\n';
  return value;
}

// ==================== Задание 1.3 ====================

void run_task_names() {
  std::cout << "\nЗадача имена\n";

  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  const int count = read_int("Введите количество имен: ", 1, 30);

  std::vector<Name> names;

  for (int i = 0; i < count; ++i) {
    while (true) {
      const std::string prompt_surname =
          "Введите фамилию для имени " + std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_given =
          "Введите личное имя для имени " + std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_patronymic =
          "Введите отчество для имени " + std::to_string(i + 1) + " или - если нет: ";

      const Name current(
          get_optional_word_value(mode, file, prompt_given, kRandomGivenNames),
          get_optional_word_value(mode, file, prompt_surname, kRandomSurnames),
          get_optional_word_value(mode, file, prompt_patronymic, kRandomPatronymics));

      if (is_empty_name(current)) {
        std::cout << "Ошибка: имя не может быть полностью пустым\n";
        continue;
      }

      names.push_back(current);
      break;
    }
  }

  std::cout << "\nРезультат\n";
  for (const Name& current : names) {
    current.print();
  }
}

// ==================== Задание 2.2 ====================

void run_task_person_with_name() {
  std::cout << "\nЗадача человек с именем\n";

  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  const int count = read_int("Введите количество людей: ", 1, 30);

  std::vector<Person> people;
  std::vector<std::string> statuses;

  for (int i = 0; i < count; ++i) {
    while (true) {
      const std::string prompt_surname =
          "Введите фамилию для человека " + std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_given =
          "Введите личное имя для человека " + std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_patronymic =
          "Введите отчество для человека " + std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_height =
          "Введите рост для человека " + std::to_string(i + 1) + ": ";

      const Name full_name(
          get_optional_word_value(mode, file, prompt_given, kRandomGivenNames),
          get_optional_word_value(mode, file, prompt_surname, kRandomSurnames),
          get_optional_word_value(mode, file, prompt_patronymic, kRandomPatronymics));

      if (is_empty_name(full_name)) {
        std::cout << "Ошибка: у человека не может быть полностью пустого имени\n";
        continue;
      }

      const int height = get_int_value(
          mode, file, prompt_height, kMinHeight, kMaxHeight);

      Person person(full_name, height);

      std::cout << "Указать отца для этого человека?\n";
      std::cout << "1. Да\n";
      std::cout << "2. Нет\n";

      const int father_choice = read_int("Ваш выбор: ", 1, 2);

      if (father_choice == 2 || people.empty()) {
        if (father_choice == 1 && people.empty()) {
          std::cout << "Отца пока выбрать нельзя, список людей пуст\n";
        }

        people.push_back(person);
        statuses.push_back("Сиротинка :(");
        break;
      }

      std::cout << "Выберите отца:\n";
      for (std::size_t j = 0; j < people.size(); ++j) {
        std::cout << (j + 1) << ". " << people[j].to_string() << '\n';
      }

      const int father_index = read_int(
          "Номер отца: ", 1, static_cast<int>(people.size()));

      person.set_father(&people[static_cast<std::size_t>(father_index - 1)]);

      people.push_back(person);
      statuses.push_back("Отец указан");
      break;
    }
  }

  std::cout << "\nРезультат\n";
  for (std::size_t i = 0; i < people.size(); ++i) {
    people[i].print();
    std::cout << "Статус: " << statuses[i] << '\n';
  }
}

// ==================== Задание 2.3 ====================

void run_task_person_with_parent() {
  std::cout << "\nЗадача человек с родителем\n";

  std::cout << "Сначала создадим трех людей\n";
  const int mode = read_mode_choice();

  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  std::vector<Person> people;

  for (int i = 0; i < 3; ++i) {
    const std::string prompt_surname =
        "Введите фамилию для человека " + std::to_string(i + 1) + " или - если нет: ";
    const std::string prompt_given =
        "Введите имя для человека " + std::to_string(i + 1) + ": ";
    const std::string prompt_patronymic =
        "Введите отчество для человека " + std::to_string(i + 1) + " или - если нет: ";
    const std::string prompt_height =
        "Введите рост для человека " + std::to_string(i + 1) + ": ";

    const Name full_name(
        get_word_value(mode, file, prompt_given, kRandomGivenNames),
        get_optional_word_value(mode, file, prompt_surname, kRandomSurnames),
        get_optional_word_value(mode, file, prompt_patronymic, kRandomPatronymics));

    people.push_back(
        Person(full_name,
               get_int_value(mode, file, prompt_height, kMinHeight, kMaxHeight)));
  }

  std::cout << "\nСозданы люди:\n";
  for (std::size_t i = 0; i < people.size(); ++i) {
    std::cout << (i + 1) << ". ";
    people[i].print();
  }

  std::cout << "\nТеперь зададим отцов\n";
  const int father_for_second = read_int(
      "Кто будет отцом для человека 2 (1..1): ", 1, 1);
  people[1].set_father(&people[static_cast<std::size_t>(father_for_second - 1)]);

  const int father_for_third = read_int(
      "Кто будет отцом для человека 3 (1..2): ", 1, 2);
  people[2].set_father(&people[static_cast<std::size_t>(father_for_third - 1)]);

  std::cout << "\nРезультат\n";
  for (const Person& person : people) {
    person.print();
  }
}

// ==================== Задание 3.1 ====================

void run_task_cities() {
  std::cout << "\nЗадача города\n";
  std::vector<City> cities;

  while (true) {
    std::cout << "\n1. Добавить город\n";
    std::cout << "2. Добавить путь\n";
    std::cout << "3. Показать все города\n";
    std::cout << "4. Пример по схеме\n";
    std::cout << "0. Выход\n";

    const int command = read_int("Введите команду: ", 0, 4);

    if (command == 0) {
      break;
    }

    if (command == 1) {
      const int add_mode = read_mode_choice();

      if (add_mode == static_cast<int>(InputMode::kKeyboard)) {
        const std::string city_name = read_phrase("Введите название города: ");
        cities.push_back(City(city_name));
        std::cout << "Город добавлен\n";
        continue;
      }

      if (add_mode == static_cast<int>(InputMode::kRandom)) {
        bool added = false;

        for (std::size_t attempt = 0; attempt < kRandomCities.size(); ++attempt) {
          const std::string candidate = random_word(kRandomCities);
          bool exists = false;

          for (const City& city : cities) {
            if (city.name() == candidate) {
              exists = true;
              break;
            }
          }

          if (!exists) {
            cities.push_back(City(candidate));
            std::cout << "Город добавлен: " << candidate << '\n';
            added = true;
            break;
          }
        }

        if (!added) {
          std::cout << "Ошибка: случайные города закончились\n";
        }
        continue;
      }

      std::ifstream input_file = open_input_file_with_retry();
      const int count = read_int("Сколько городов считать из файла: ", 1, 20);

      for (int i = 0; i < count; ++i) {
        const std::string city_name = read_word_from_file(input_file);
        if (city_name.empty()) {
          std::cout << "В файле больше нет городов\n";
          break;
        }
        cities.push_back(City(city_name));
        std::cout << "Город добавлен: " << city_name << '\n';
      }

      continue;
    }

    if (command == 2) {
      if (cities.size() < 2) {
        std::cout << "Сначала добавьте хотя бы 2 города\n";
        continue;
      }

      std::cout << "Список городов:\n";
      for (std::size_t i = 0; i < cities.size(); ++i) {
        std::cout << (i + 1) << ". " << cities[i].name() << '\n';
      }

      int from_index = 0;
      int to_index = 0;

      while (true) {
        from_index = read_int("Из какого города: ", 1,
                              static_cast<int>(cities.size()));
        to_index = read_int("В какой город: ", 1,
                            static_cast<int>(cities.size()));

        if (from_index == to_index) {
          std::cout << "Ошибка: путь в тот же город нельзя\n";
          continue;
        }

        bool exists = false;
        const std::vector<std::pair<std::string, int>>& routes =
            cities[static_cast<std::size_t>(from_index - 1)].routes();

        for (const std::pair<std::string, int>& route : routes) {
          if (route.first ==
              cities[static_cast<std::size_t>(to_index - 1)].name()) {
            exists = true;
            break;
          }
        }

        if (exists) {
          std::cout << "Ошибка: такой путь уже есть\n";
          continue;
        }

        break;
      }

      const int cost = read_int("Стоимость пути: ", kMinCost, kMaxCost);
      cities[static_cast<std::size_t>(from_index - 1)].add_route(
          cities[static_cast<std::size_t>(to_index - 1)].name(), cost);

      std::cout << "Путь добавлен\n";
      continue;
    }

    if (command == 3) {
      if (cities.empty()) {
        std::cout << "Города еще не добавлены\n";
        continue;
      }

      std::cout << "Текущий граф\n";
      for (std::size_t i = 0; i < cities.size(); ++i) {
        std::cout << (i + 1) << " - ";
        cities[i].print();
        std::cout << '\n';
      }
      continue;
    }

    if (command == 4) {
      std::vector<City> example;

      City a("A");
      City b("B");
      City c("C");
      City d("D");
      City e("E");
      City f("F");

      a.add_route("F", 1);
      a.add_route("D", 6);

      b.add_route("A", 5);
      b.add_route("C", 3);

      c.add_route("B", 3);
      c.add_route("D", 4);

      d.add_route("C", 4);
      d.add_route("E", 2);

      e.add_route("F", 2);

      f.add_route("A", 1);
      f.add_route("B", 1);
      f.add_route("E", 2);

      example.push_back(a);
      example.push_back(b);
      example.push_back(c);
      example.push_back(d);
      example.push_back(e);
      example.push_back(f);

      std::cout << "Пример графа\n";
      for (std::size_t i = 0; i < example.size(); ++i) {
        std::cout << (i + 1) << " - ";
        example[i].print();
        std::cout << '\n';
      }
    }
  }
}

// ==================== Задание 4.5 ====================

void run_task_create_names() {
  std::cout << "\nЗадача создаем имена\n";

  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  const int count = read_int("Введите количество имен: ", 1, 30);
  std::vector<Name> names;

  for (int i = 0; i < count; ++i) {
    std::cout << "\nДля имени " << (i + 1) << " выберите тип создания\n";
    std::cout << "1. Только личное имя\n";
    std::cout << "2. Личное имя и фамилия\n";
    std::cout << "3. Личное имя, фамилия и отчество\n";

    const int create_type = read_int("Ваш выбор: ", 1, 3);

    const std::string prompt_given =
        "Введите личное имя: ";
    const std::string prompt_surname =
        "Введите фамилию: ";
    const std::string prompt_patronymic =
        "Введите отчество: ";

    if (create_type == 1) {
      names.push_back(Name(
          get_word_value(mode, file, prompt_given, kRandomGivenNames)));
      continue;
    }

    if (create_type == 2) {
      names.push_back(Name(
          get_word_value(mode, file, prompt_given, kRandomGivenNames),
          get_word_value(mode, file, prompt_surname, kRandomSurnames)));
      continue;
    }

    names.push_back(Name(
        get_word_value(mode, file, prompt_given, kRandomGivenNames),
        get_word_value(mode, file, prompt_surname, kRandomSurnames),
        get_word_value(mode, file, prompt_patronymic, kRandomPatronymics)));
  }

  std::cout << "\nРезультат\n";
  for (const Name& name : names) {
    name.print();
  }
}

// ==================== Задание 4.6 ====================

void run_task_create_people() {
  std::cout << "\nЗадача создаем человека\n";

  std::vector<Person> people;
  const int count = read_int("Сколько людей создать: ", 1, 10);

  for (int i = 0; i < count; ++i) {
    std::cout << "\nСоздание человека " << (i + 1) << '\n';
    std::cout << "1. Имя строкой и рост\n";
    std::cout << "2. Имя строкой, рост и отец\n";
    std::cout << "3. Имя как объект Name и рост\n";
    std::cout << "4. Имя как объект Name, рост и отец\n";

    const int create_type = read_int("Ваш выбор: ", 1, 4);

    if (create_type == 1) {
      const std::string given_name = read_word("Введите имя: ");
      const int height = read_int("Введите рост: ", kMinHeight, kMaxHeight);
      people.push_back(Person(given_name, height));
      continue;
    }

    if (create_type == 2) {
      const std::string given_name = read_word("Введите имя: ");
      const int height = read_int("Введите рост: ", kMinHeight, kMaxHeight);

      if (people.empty()) {
        std::cout << "Отца пока нет, человек будет создан без отца\n";
        people.push_back(Person(given_name, height));
        continue;
      }

      std::cout << "Выберите отца:\n";
      for (std::size_t j = 0; j < people.size(); ++j) {
        std::cout << (j + 1) << ". " << people[j].to_string() << '\n';
      }

      const int father_index = read_int(
          "Номер отца: ", 1, static_cast<int>(people.size()));

      people.push_back(Person(
          given_name,
          height,
          &people[static_cast<std::size_t>(father_index - 1)]));
      continue;
    }

    if (create_type == 3) {
      std::cout << "Как создать объект Name?\n";
      std::cout << "1. Только имя\n";
      std::cout << "2. Имя и фамилия\n";
      std::cout << "3. Имя, фамилия и отчество\n";

      const int name_type = read_int("Ваш выбор: ", 1, 3);
      const int height = read_int("Введите рост: ", kMinHeight, kMaxHeight);

      if (name_type == 1) {
        const std::string given_name = read_word("Введите имя: ");
        people.push_back(Person(Name(given_name), height));
        continue;
      }

      if (name_type == 2) {
        const std::string given_name = read_word("Введите имя: ");
        const std::string surname = read_word("Введите фамилию: ");
        people.push_back(Person(Name(given_name, surname), height));
        continue;
      }

      const std::string given_name = read_word("Введите имя: ");
      const std::string surname = read_word("Введите фамилию: ");
      const std::string patronymic = read_word("Введите отчество: ");
      people.push_back(Person(Name(given_name, surname, patronymic), height));
      continue;
    }

    std::cout << "Как создать объект Name?\n";
    std::cout << "1. Только имя\n";
    std::cout << "2. Имя и фамилия\n";
    std::cout << "3. Имя, фамилия и отчество\n";

    const int name_type = read_int("Ваш выбор: ", 1, 3);
    const int height = read_int("Введите рост: ", kMinHeight, kMaxHeight);

    if (people.empty()) {
      std::cout << "Отца пока нет, создаем без отца\n";

      if (name_type == 1) {
        const std::string given_name = read_word("Введите имя: ");
        people.push_back(Person(Name(given_name), height));
      } else if (name_type == 2) {
        const std::string given_name = read_word("Введите имя: ");
        const std::string surname = read_word("Введите фамилию: ");
        people.push_back(Person(Name(given_name, surname), height));
      } else {
        const std::string given_name = read_word("Введите имя: ");
        const std::string surname = read_word("Введите фамилию: ");
        const std::string patronymic = read_word("Введите отчество: ");
        people.push_back(Person(Name(given_name, surname, patronymic), height));
      }
      continue;
    }

    std::cout << "Выберите отца:\n";
    for (std::size_t j = 0; j < people.size(); ++j) {
      std::cout << (j + 1) << ". " << people[j].to_string() << '\n';
    }

    const int father_index = read_int(
        "Номер отца: ", 1, static_cast<int>(people.size()));
    Person* father = &people[static_cast<std::size_t>(father_index - 1)];

    if (name_type == 1) {
      const std::string given_name = read_word("Введите имя: ");
      people.push_back(Person(Name(given_name), height, father));
    } else if (name_type == 2) {
      const std::string given_name = read_word("Введите имя: ");
      const std::string surname = read_word("Введите фамилию: ");
      people.push_back(Person(Name(given_name, surname), height, father));
    } else {
      const std::string given_name = read_word("Введите имя: ");
      const std::string surname = read_word("Введите фамилию: ");
      const std::string patronymic = read_word("Введите отчество: ");
      people.push_back(Person(Name(given_name, surname, patronymic), height, father));
    }
  }

  std::cout << "\nРезультат\n";
  for (const Person& person : people) {
    person.print();
  }
}

// ==================== Задание 5.2 ====================

void run_task_cat() {
  std::cout << "\nЗадача кот мяукает\n";

  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  const std::string cat_name =
      get_word_value(mode, file, "Введите имя кота: ", kRandomGivenNames);

  Cat cat(cat_name);

  std::cout << "\nРезультат\n";
  cat.print();
  cat.meow();

  const int count = get_int_value(
      mode, file, "Сколько раз мяукнуть: ", 1, 10);
  cat.meow(count);
}