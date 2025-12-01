#include <iostream>
#include <vector>

class Unit {
public:
    virtual void behave() = 0;

    virtual ~Unit() = default;

    virtual Unit* copy() const = 0;
};

class Elf : public Unit {
public:
    void behave() override {
        std::cout << "Elf behaves\n";
    }

    Unit* copy() const override {
        return new Elf(*this);
    }
};

class Dwarf : public Unit {
public:
    void behave() override {
        std::cout << "Dwarf behaves\n";
    }

    Unit* copy() const override {
        return new Dwarf(*this);
    }
};

class Man : public Unit {
public:
    void behave() override {
        std::cout << "Man behaves\n";
    }

    Unit* copy() const override {
        return new Man(*this);
    }
};


class UnitFactory {
public:
    auto createElf() const {
        return s_elf.copy();
    }

    auto createDwarf() const {
        return s_dwarf.copy();
    }

    auto createMan() const {
        return s_man.copy();
    }

private :
    static inline Elf const s_elf;

    static inline Dwarf const s_dwarf;

    static inline Man const s_man;
};

class Army : public Unit {
public:
    ~Army() {
        for (auto& unit : units) {
            delete unit;
        }
    }

    void add(Unit* unit) {
        units.push_back(std::move(unit));
    }

    void behave() override {
        for (auto& unit : units) unit->behave();
    }

    Unit* copy() const override {
        Army* result = new Army();

        for (auto unit : units) result->add(unit->copy());

        return result;
    }

private:
    std::vector<Unit*> units;
};

class GameState {
public:
    virtual void next() = 0;

    virtual ~GameState() = default;
};

class Peace : public GameState {
public:
    void next() override {
        std::cout << "Peace... Prepare for battle\n";
    }
};

class War : public GameState {
public:
    void next() override {
        std::cout << "War! Units fight\n";
    }
};

class Game {
public:
    Game(GameState* state) : state(state) {}

    ~Game() {
        delete state;
    }

    void changeState(GameState* newState) {
        delete state;
        state = newState;
    }

    void update() {
        state->next();
    }

private:
    GameState* state;
};

auto make_army(
    const UnitFactory& factory,
    std::size_t elfs_count,
    std::size_t dwarfs_count,
    std::size_t men_count) {
    
    Army* army = new Army();

    for (auto i = 0uz; i < elfs_count; ++i) army->add(factory.createElf());

    for (auto i = 0uz; i < dwarfs_count; ++i) army->add(factory.createDwarf());

    for (auto i = 0uz; i < men_count; ++i) army->add(factory.createMan());

    return army;
}

int main() {
    UnitFactory factory;
    Army* army = make_army(factory, 2, 0, 3);

    Game game = Game(new Peace);
    game.update();
    game.changeState(new War);
    game.update();
    army->behave();

    delete army;
}
