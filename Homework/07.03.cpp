void test(Person const & person)
{
    // могут пробрасываться пользовытельские исключения при вызове name() или std::ios_base::failure
    std::cout << "test : " << person.name() << '\n';

    // // могут пробрасываться пользовытельские исключения при вызове grade() или salary()
    if (person.grade() == 10 || person.salary() > 1'000'000) // нормальное ветвление them -> успех, else -> ошибка
    {
        save(Status::success, person.id()); // могут пробрасываться пользовытельские исключения при вызове save() или id()
    }
    else
    {
        save(Status::failure, person.id()); // могут пробрасываться пользовытельские исключения при вызове save() или id()
    }
}
