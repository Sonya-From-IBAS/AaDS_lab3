#include <iostream>
#include <vector>

//конструктор копирования, оператор присваивания и деструктор генерируются неявно компилятором.
template<class T>
class Vector {
private:
    size_t size;
    std::vector<T> value;
public:

    size_t GetSize() const {
        return size;
    }

    Vector(size_t SIZE) {
        size = SIZE;
        for (size_t i = 0; i < size; i++)
        {
            value.push_back(T(0));
        }
    }

    Vector(std::vector<T>& v) {
        size = v.size();
        for (auto i : v) {
            value.push_back(i);
        }
    }

    Vector(const Vector<T>& VALUE) = default;

    ~Vector() = default;

    Vector<T>& operator=(const Vector<T>& v) = default;

    Vector& operator +=(const Vector& v) {
        if (size != v.size) throw std::exception("Size doesn't match");
        for (int i = 0; i < size; i++) {
            value[i] += v.value[i];
        }
        return *this;
    }

    Vector& operator -=(const Vector& v) {
        if (size != v.size) throw std::exception("Size doesn't match");
        for (int i = 0; i < size; i++) {
            value[i] -= v.value[i];
        }
        return *this;
    }

    Vector& operator *=(T scalar) {
        for (int i = 0; i < size; i++) {
            value[i] *= scalar;
        }
        return *this;
    }

    Vector& operator /=(T scalar) {
        if (scalar == T(0)) throw std::exception("Division by zero");
        for (int i = 0; i < size; i++) {
            value[i] /= scalar;
        }
        return *this;
    }


    //• оператор [] для чтения/записи элемента вектора по указанному индексу;
    T& operator[](size_t index) {
        if (index >= size) throw std::exception("Invalid index");
        return value[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::exception("Invalid index");
        return value[index];
    }


    Vector operator*(T scalar) {
        Vector<T> copy(value);
        copy *= scalar;
        return copy;
    }


    auto begin() const {
        return value.begin();
    }

    auto end() const {
        return value.end();
    }

    std::vector<T> GetVector() const {
        return value;
    }

};


//• операторы сложения и вычитания векторов;
template<class T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2)
{
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    Vector<T> copy = v1;
    copy += v2;
    return copy;
}

template<class T>
Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2)
{
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    Vector<T> copy = v1;
    copy -= v2;
    return copy;
}

//• оператор умножения, выполняющий скалярное произведение векторов;
template<class T>
T operator*(const Vector<T>& v1, const Vector<T>& v2)
{
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    T result = T(0);
    for (int i = 0; i < v1.GetSize(); i++) {
        result += v1[i] * v2[i];
    }
    return result;
}


//• оператор умножения вектора на скаляр(обеспечить коммутативность);
template<class T>
Vector<T> operator*(const Vector<T>& v, T scalar)
{
    Vector<T> copy = v;
    copy *= scalar;
    return copy;
}

template<class T>
Vector<T> operator*(double scalar, const Vector<T>& v)
{
    Vector<T> copy = v;
    copy *= scalar;
    return copy;
}

//• оператор деления вектора на скаляр.
template<class T>
Vector<T> operator/(const Vector<T>& v, T scalar)
{
    Vector<T> copy = v;
    copy /= scalar;
    return copy;
}

template<class T>
std::ostream& operator <<(std::ostream& out, const Vector<T>& v) {
    for (auto i : v) {
        out << i << " ";
    }
    out << "\n";
    return out;
}

template<class T>
bool is_equal(T x, T y) {
    return std::fabs(x - y) < std::numeric_limits<T>::epsilon();
    // epsilon возвращает разницу между 1 и наименьшим значением больше 1, которое этот тип данных может представлять
}

template<class T>
//сравнивать отдельно реальные и комплексные части
bool operator ==(const Vector<T>& v1, const Vector<T>& v2) {
    return v1.GetVector() == v2.GetVector();
}

template<class T>
bool operator !=(const Vector<T>& v1, const Vector<T>& v2) {
    return!(v1 == v2);
}

//Задача: Посчитать площадь треугольника, две стороны которого заданы радиус - векторами a и b.
template<class T>
double vector_len(const Vector<T>& v) {
    double len = 0.0;
    for (int i = 0; i < v.GetSize(); i++) {
        len += std::pow(v[i], 2);
    }
    return sqrt(len);
}

template<class T>
double get_square(const Vector<T>& v1, const Vector<T>& v2) {
    double cos_alfa = (double)(v1 * v2) / (double)(vector_len(v1) * vector_len(v2));
    double sin_alfa = std::sqrt(1 - std::pow(cos_alfa, 2));
    double square = vector_len(v1) * vector_len(v2) * sin_alfa / 2;
    return square;
}


int main()
{
    int what_type_square;
    bool programm_runner = true;

    size_t array_size;
    int a;
    float b;
    double c;


    while (programm_runner) {
        std::cout << "Choose with which type of data we will calculate the area:" << std::endl;
        std::cout << "1) int" << std::endl;
        std::cout << "2) float" << std::endl;
        std::cout << "3) double" << std::endl;
        std::cout << "4) exit programm" << std::endl;
        std::cin >> what_type_square;

        switch (what_type_square)
        {
        case 1:
        {
            system("cls");

            std::cout << "you have selected the int data type" << std::endl;
            std::cout << "you have to create and fill two vectors" << std::endl;
            std::cout << "and then the program will calculate the square of the triangle" << std::endl;
            std::cout << "enter size of first vector: ";
            std::cin >> array_size;
            std::vector<int> a1;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "a" << i << " = ";
                std::cin >> a;
                a1.push_back(a);
            }
            Vector<int> v1(a1);

            std::cout << "enter size of second vector: ";
            std::cin >> array_size;
            std::vector<int> a2;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "a" << i << " = ";
                std::cin >> a;
                a2.push_back(a);
            }
            Vector<int> v2(a2);
            try {
                std::cout << "the square of the triangle:" << get_square(v1, v2) << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "Error:" << std::endl;
                std::cout << e.what() << std::endl;
            }
            a1.clear();
            a2.clear();
            break;
        }
        case 2:
        {
            system("cls");
            std::cout << "you have selected the float data type" << std::endl;
            std::cout << "you have to create and fill two vectors" << std::endl;
            std::cout << "and then the program will calculate the square of the triangle" << std::endl;
            std::cout << "enter size of first vector: ";
            std::cin >> array_size;
            std::vector<float>b1;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "b" << i << " = ";
                std::cin >> b;
                b1.push_back(b);
            }
            Vector<float> v1(b1);

            std::cout << "enter size of second vector: ";
            std::cin >> array_size;
            std::vector<float>b2;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "b" << i << " = ";
                std::cin >> b;
                b2.push_back(b);
            }
            Vector<float> v2(b2);
            try {
                std::cout << "the square of the triangle:" << get_square(v1, v2) << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "Error:" << std::endl;
                std::cout << e.what() << std::endl;
            }
            b1.clear();
            b2.clear();
            break;
        }
        case 3:
        {
            system("cls");
            std::cout << "you have selected the double data type" << std::endl;
            std::cout << "you have to create and fill two vectors" << std::endl;
            std::cout << "and then the program will calculate the square of the triangle" << std::endl;
            std::cout << "enter size of first vector: ";
            std::cin >> array_size;
            std::vector<double> c1;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "c" << i << " = ";
                std::cin >> c;
                c1.push_back(c);
            }
            Vector<double> v1(c1);

            std::cout << "enter size of second vector: ";
            std::cin >> array_size;
            std::vector<double> c2;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "c" << i << " = ";
                std::cin >> c;
                c2.push_back(c);
            }
            Vector<double> v2(c2);

            try {
                std::cout << "the square of the triangle:" << get_square(v1, v2) << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "Error:" << std::endl;
                std::cout << e.what() << std::endl;
            }
            c1.clear();
            c2.clear();
            break;
        }
        case 4:
            programm_runner = false;
            system("cls");
            std::cout << "you have exited the program" << std::endl;
            break;
        default:
            std::cout << "you have selected non - existent option, try it again" << std::endl;
            break;
        }
        system("pause");
        system("cls");
    }
}