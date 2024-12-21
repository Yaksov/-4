#include <iostream>
#include <vector>
#include <stdexcept>

class Person {
public:
    virtual void display() const {
        std::cout << "Human" << std::endl;
    }
    virtual ~Person() {}
};

class Preschooler : public Person {
public:
    void display() const override {
        std::cout << "det sad" << std::endl;
    }
};

class Schoolchild : public Person {
public:
    void display() const override {
        std::cout << "pupil" << std::endl;
    }
};

class Student : public Person {
public:
    void display() const override {
        std::cout << "student" << std::endl;
    }
};

class Worker : public Person {
public:
    void display() const override {
        std::cout << "worker" << std::endl;
    }
};

template <typename T>
class ObjectArray {
private:
    T** objects;
    size_t size;

public:
    ObjectArray(size_t size) : size(size) {
        objects = new T * [size];
        for (size_t i = 0; i < size; ++i) {
            objects[i] = nullptr;
        }
    }

    ~ObjectArray() {
        for (size_t i = 0; i < size; ++i) {
            delete objects[i];
        }
        delete[] objects;
    }

    T*& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("index out of a massive.");
        }
        return objects[index];
    }

    const T* operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("index out of a massive.");
        }
        return objects[index];
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    try {
        ObjectArray<Person> people(4);

        people[0] = new Preschooler();
        people[1] = new Schoolchild();
        people[2] = new Student();
        people[3] = new Worker();

        for (size_t i = 0; i < people.getSize(); ++i) {
            people[i]->display();
        }

        try {
            people[4]->display(); 
        }
        catch (const std::out_of_range& e) {
            std::cerr << "error: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "global error: " << e.what() << std::endl;
    }

    return 0;
}
