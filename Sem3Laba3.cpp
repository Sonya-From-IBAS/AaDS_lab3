#include <iostream>
#include <vector>
#include <complex>

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

template<class T>                   //для комплексных
std::complex<T> operator*(const Vector<std::complex<T>>& v1, const Vector<std::complex<T>>& v2)
{
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    std::complex<T> result(0, 0);
    for (int i = 0; i < v1.GetSize(); i++) {
        result += std::complex<T>(v1[i].real() * v2[i].real() - v1[i].imag() * v2[i].imag(), v1[i].real() * v2[i].imag() + v1[i].imag() * v2[i].real());
    }
    return result;
}


template<class T>               //для задачки
double multiple(const Vector<std::complex<T>>& v1, const Vector<std::complex<T>>& v2)
{
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    std::complex<T> result(0, 0);
    for (int i = 0; i < v1.GetSize(); i++) {
        result += std::complex<T>(v1[i].real() * v2[i].real() - v1[i].imag() * v2[i].imag(), v1[i].real() * v2[i].imag() + v1[i].imag() * v2[i].real());
    }
    return result.real();
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
bool operator ==(const Vector<std::complex<T>>& v1, const Vector<std::complex<T>>& v2) {
    if (v1.GetSize() != v2.GetSize()) throw std::exception("Size doesn't match");
    for (int i = 0; i < v1.GetSize(); i++) {
        if (!is_equal(v1[i].real(), v2[i].real()) || !is_equal(v1[i].imag(), v2[i].imag())) return false;
    }
    return true;
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
T vector_len(const Vector<std::complex<T>>& v) {
    T len = 0;
    for (int i = 0; i < v.GetSize(); i++) {
        len += std::abs(v[i]);
    }
    return len;
}


template<class T>
double get_square(const Vector<T>& v1, const Vector<T>& v2) {
    double cos_alfa = (double)(v1 * v2) / (double)(vector_len(v1) * vector_len(v2));
    double sin_alfa = std::sqrt(1 - std::pow(cos_alfa, 2));
    double square = vector_len(v1) * vector_len(v2) * sin_alfa / 2;
    return square;
}


template<class T>
T get_square(const Vector<std::complex<T>>& v1, const Vector<std::complex<T>>& v2) {

    double cos_alfa = multiple(v1, v2) / (vector_len(v1) * vector_len(v2));
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
        std::cout << "4) std::complex<float>" << std::endl;
        std::cout << "5) std::complex<double>" << std::endl;
        std::cout << "6) exit programm" << std::endl;
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
        {
            system("cls");
            std::cout << "you have selected the std::complex<float> data type" << std::endl;
            std::cout << "you have to create and fill two vectors" << std::endl;
            std::cout << "and then the program will calculate the square of the triangle" << std::endl;
            std::cout << "enter size of first vector: ";
            std::cin >> array_size;
            std::vector<std::complex<float>> f1;
            std::vector<std::complex<float>> f2;
            std::cout << "fill vector: " << std::endl;
            float data_real;
            float data_imag;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "f" << i << "(real) = ";
                std::cin >> data_real;

                std::cout << "f" << i << "(imag) = ";
                std::cin >> data_imag;
                f1.push_back(std::complex<float>(data_real, data_imag));
            }
            Vector<std::complex<float>> v1(f1);

            std::cout << "enter size of second vector: ";
            std::cin >> array_size;
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "f" << i << "(real) = ";
                std::cin >> data_real;

                std::cout << "f" << i << "(imag) = ";
                std::cin >> data_imag;
                f2.push_back(std::complex<float>(data_real, data_imag));
            }
            Vector<std::complex<float>> v2(f2);
            try {
                std::cout << "the square of the triangle:" << get_square(v1, v2) << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "Error:" << std::endl;
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            std::cout << "you have selected the std::complex<double> data type" << std::endl;
            std::cout << "you have to create and fill two vectors" << std::endl;
            std::cout << "and then the program will calculate the square of the triangle" << std::endl;
            std::cout << "enter size of first vector: ";
            std::cin >> array_size;
            std::vector<std::complex<double>> d1;
            std::vector<std::complex<double>> d2;
            std::cout << "fill vector: " << std::endl;
            double data_real;
            double data_imag;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "d" << i << "(real) = ";
                std::cin >> data_real;

                std::cout << "d" << i << "(imag) = ";
                std::cin >> data_imag;
                d1.push_back(std::complex<double>(data_real, data_imag));
            }
            Vector<std::complex<double>> v1(d1);

            std::cout << "enter size of second vector: ";
            std::cin >> array_size;
           
            std::cout << "fill vector: " << std::endl;
            for (size_t i = 0; i < array_size; i++)
            {
                std::cout << "d" << i << "(real) = ";
                std::cin >> data_real;

                std::cout << "d" << i << "(imag) = ";
                std::cin >> data_imag;
                d2.push_back(std::complex<double>(data_real, data_imag));
            }
            Vector<std::complex<double>> v2(d2);

            try {
                std::cout << "the square of the triangle:" << get_square(v1, v2) << std::endl;
            }
            catch (std::exception& e) {
                std::cout << "Error:" << std::endl;
                std::cout << e.what() << std::endl;
            }
            break;
        }
        case 6:
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


//int main() {
//    
//    //int a[2] = { 1,4 };
//    //float b[2] = { 2,9 };
//    //double c[2] = { 3,9 };
//
//
//    std::vector<int>a(1,4);
//    std::vector<float>b(2,9);
//    std::vector<double>c(3,9);
//
//    Vector<int> v1(a);
//    Vector<float> v2(b);
//    Vector<double> v3(c);
//
//
//
//    std::complex<float>f1(1, 0);
//    std::complex<float>f2(1, 0);
//    std::complex<float>e1(0, 0);
//    std::complex<float>e2(1, 0);
//
//    std::vector<std::complex<float> > f;
//    f.push_back(f1);
//    f.push_back(f2);
//
//    std::vector<std::complex<float> > e;
//    e.push_back(e1);
//    e.push_back(e2);
//
//    Vector<std::complex<float> > v4(f);
//    Vector<std::complex<float> > v5(e);
//
//
//    std::cout << vector_len(v1) << std::endl;
//    std::cout << vector_len(v2) << std::endl;
//    std::cout << vector_len(v3) << std::endl;
//    std::cout << vector_len(v4) << std::endl;
//    std::cout << vector_len(v5) << std::endl;
//    std::cout << get_square(v4, v5) << std::endl;
//    return 0;
//}