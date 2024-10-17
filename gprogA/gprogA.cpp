#include <iostream>
#include <string>

class Bow; // Предварительное объявление класса

// Объявления дружественных функций
Bow* createBow(double str, const std::string& bsm);
void destroyBow(Bow* bow);

class Bow {
private:
    double strength;          // Сила лука
    std::string bowStringMat; // Материал тетивы
    static int objectCount;   // Статический счетчик объектов

    // Закрытые конструкторы и деструктор
    Bow(double str, const std::string& bsm) : strength(str), bowStringMat(bsm) {
        objectCount++;  // Увеличиваем счетчик при создании объекта
        std::cout << "Bow created: Strength = " << strength << ", Material = " << bowStringMat << "\n";
    }

    ~Bow() {
        objectCount--;  // Уменьшаем счетчик при уничтожении объекта
        std::cout << "Bow destroyed: Strength = " << strength << ", Material = " << bowStringMat << "\n";
    }

public:
    // Дружественные функции, которые могут обращаться к приватным членам
    friend Bow* createBow(double str, const std::string& bsm);
    friend void destroyBow(Bow* bow);

    // Метод для изменения тетивы и силы
    void restring(const std::string& newBowStringMat) {
        bowStringMat = newBowStringMat;
        updateStrength();  // Обновляем силу в зависимости от материала
        std::cout << "Bow string material changed to: " << bowStringMat
            << ", New Strength = " << strength << "\n";
    }

    // Метод для тестирования класса
    static void test() {
        std::cout << "Starting tests...\n";

        Bow* bow1 = createBow(50.0, "Synthetic");
        Bow* bow2 = createBow(60.0, "Natural Fiber");

        std::cout << "Initial Object Count: " << getObjectCount() << "\n";

        // Изменение тетивы и проверка изменения силы
        bow1->restring("Dacron");
        bow2->restring("Kevlar");

        std::cout << "Final Object Count: " << getObjectCount() << "\n";

        destroyBow(bow1);
        destroyBow(bow2);

        std::cout << "Final Object Count after deletion: " << getObjectCount() << "\n";
        std::cout << "Tests completed.\n";
    }

    // Статический метод для получения количества объектов
    static int getObjectCount() {
        return objectCount;
    }

private:
    // Метод для обновления силы в зависимости от материала
    void updateStrength() {
        if (bowStringMat == "Synthetic") {
            strength = 50.0;
        }
        else if (bowStringMat == "Natural Fiber") {
            strength = 60.0;
        }
        else if (bowStringMat == "Dacron") {
            strength = 55.0;
        }
        else if (bowStringMat == "Kevlar") {
            strength = 70.0;
        }
        else {
            strength = 40.0; // Значение по умолчанию для неизвестного материала
        }
    }
};

// Инициализация статического поля
int Bow::objectCount = 0;

// Реализация дружественной функции для создания объекта
Bow* createBow(double str, const std::string& bsm) {
    return new Bow(str, bsm);
}

// Реализация дружественной функции для уничтожения объекта
void destroyBow(Bow* bow) {
    delete bow;
}

int main() {
    Bow::test();  // Запускаем тестирование

    return 0;
}
