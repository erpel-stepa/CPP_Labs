#ifndef MODULE_H_
#define MODULE_H_

#include <fstream>
#include <string>
#include <utility>
#include <vector>

enum class InputMode {
  kKeyboard = 1,
  kRandom = 2,
  kFile = 3
};

// 1 сделать проверку на пустое имя
// 2 объединить 2 задания в одно и сделать проверку на то есть отец или нет


class Name {
 public:
  // конструкторы класса name
  Name();
  explicit Name(const std::string& given_name);
  Name(const std::string& given_name, const std::string& surname);
  Name(const std::string& given_name,
       const std::string& surname,
       const std::string& patronymic);
  Name(const Name& other);

  // оператор =
  Name& operator=(const Name& other);

  // деструктор класса name
  ~Name() = default;

  const std::string& surname() const;
  const std::string& given_name() const;
  const std::string& patronymic() const;

  void set_surname(const std::string& surname);
  void set_given_name(const std::string& given_name);
  void set_patronymic(const std::string& patronymic);

  bool has_surname() const;
  bool has_given_name() const;
  bool has_patronymic() const;

  std::string to_string() const;
  void print() const;

 private:
  std::string surname_;
  std::string given_name_;
  std::string patronymic_;
};

class Person {
 public:
  // конструкторы класса person
  Person();
  Person(const std::string& given_name, int height);
  Person(const std::string& given_name, int height, Person* father);
  Person(const Name& name, int height);
  Person(const Name& name, int height, Person* father);
  Person(const Person& other);

  // оператор =
  Person& operator=(const Person& other);

  // деструктор класса person
  ~Person() = default;

  const Name& name() const;
  int height() const;
  Person* father() const;

  void set_name(const Name& name);
  void set_height(int height);
  void set_father(Person* father);

  std::string to_string() const;
  void print() const;

 private:
  void fill_name_from_father();

  Name name_;
  int height_;
  Person* father_;
};

class City {
 public:
  // конструкторы класса city
  City();
  explicit City(const std::string& name);
  City(const std::string& name,
       const std::vector<std::pair<std::string, int>>& routes);
  City(const City& other);

  // оператор =
  City& operator=(const City& other);

  // деструктор класса city
  ~City() = default;

  const std::string& name() const;
  const std::vector<std::pair<std::string, int>>& routes() const;

  void set_name(const std::string& name);
  void add_route(const std::string& to_city, int cost);
  void clear_routes();

  std::string to_string() const;
  void print() const;

 private:
  std::string name_;
  std::vector<std::pair<std::string, int>> routes_;
};

class Cat {
 public:
  // конструкторы класса cat
  Cat();
  explicit Cat(const std::string& name);
  Cat(const Cat& other);

  // оператор =
  Cat& operator=(const Cat& other);

  // деструктор класса cat
  ~Cat() = default;

  const std::string& name() const;

  void set_name(const std::string& name);

  std::string to_string() const;
  void print() const;

  void meow() const;
  void meow(int count) const;

 private:
  std::string name_;
};

bool is_valid_word(const std::string& text);
bool is_valid_phrase(const std::string& text);

std::string read_non_empty_line(const std::string& prompt);
std::string read_word(const std::string& prompt);
std::string read_phrase(const std::string& prompt);
std::string read_optional_word(const std::string& prompt);
int read_int(const std::string& prompt, int min_value, int max_value);

int read_mode_choice();
std::string read_file_path();
std::ifstream open_input_file_with_retry();

int random_int(int min_value, int max_value);
std::string random_word(const std::vector<std::string>& values);

std::string read_word_from_file(std::ifstream& file);
std::string get_word_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    const std::vector<std::string>& random_values);

std::string get_optional_word_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    const std::vector<std::string>& random_values);

int get_int_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    int min_value,
    int max_value);

void run_task_names();
void run_task_person_with_name();
void run_task_person_with_parent();
void run_task_cities();
void run_task_create_names();
void run_task_create_people();
void run_task_cat();

#endif