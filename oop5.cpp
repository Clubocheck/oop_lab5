#include<iostream>
#include<vector>
using namespace std;

class Base {//родительский класс
public:
	//конструкторы
	Base() {
		cout << "Base()" << endl;
	}
	Base(Base* obj) {
		cout << "Base(Base* obj)" << endl;
	}
	Base(Base& obj) {
		cout << "Base(Base& obj)" << endl;
	}

	//виртуальный диструктор
	virtual ~Base() {
		cout << "~Base()" << endl;
	}

	//методы
	void doSomething1() {//невиртуальный метод 1
		cout << "Base::doSomething1" << endl;
		doSomething3();
	}
	void doSomething2() {//невиртуальный метод 2
		cout << "Base::doSomething1" << endl;
		doSomething4();
	}
	void doSomething3() {//невиртуальный метод 3
		cout << "Base::doSomething2 non virtual" << endl;
	}
	virtual void doSomething4() {//виртуальный метод 4
		cout << "Base::doSomething2 virtual" << endl;
	}

	virtual string classname() {//метод возвращения имени класс объекта
		return "Base";
	}
	virtual bool IsA(string classname) {//метод для предварительной проверки при приведении типа
		return classname == "Base";
	}
	string test() {
		return "Im Base";
	}
};

class Desk  : public Base {//Дочерний класс
public:
	//конструкторы
	Desk(){
		cout << "Desk()" << endl;
	}
	Desk(Desk* obj){
		cout << "Desk(Desk* obj)" << endl;
	}
	Desk(Desk& obj){
		cout << "Desk(Desk& obj)" << endl;
	}
	//виртульный деструктор
	virtual ~Desk() {
		cout << "~Desk()" << endl;
	}

	void doSomething3() {//невиртуальный метод 3
		cout << "Desk::doSomething2 non virtual" << endl;
	}
	void doSomething4() override{//виртуальный метод 4
		cout << "Desk::doSomething2 virtual" << endl;
	}
	string classname() override {
		return "Desk";
	}
	bool IsA(string classname) override {
		return classname == "Desk";
	}
	string test() {
		return "Im Desk";
	}
};

class SonDesk: public Base {
public:
	bool IsA(string classname) {
		return classname == "SonDesk";
	}
	string classname() override {
		return "SonDesk";
	}
	string test() {
		return "Im SonDesk";
	}
};

void func() {
	cout << "func()" << endl;
}
void func(Base* obj) {
	cout << "func(Base* obj)" << endl;
	(static_cast<Desk*>(obj))->doSomething3();
}
void func(Base& obj) {
	cout << "func(Base& obj)" << endl;
	(static_cast<Desk*>(&obj))->doSomething3();
}
// Объявление функции func1, которая возвращает объект класса Base по значению
// В данном случае создаётся статический объект, который будет жить до конца работы программы. При каждом вызове функции будет
// возвращаться ссылка на этот объект. Это позволяет избежать проблем с утечками памяти, но может привести к проблемам с многопоточностью.
Base func1() {
	// Создание локальной переменной типа Base
	Base local;
	// Возврат локальной переменной по значению
	return local;
}

// Объявление функции func2, которая возвращает указатель на объект класса Base

Base* func2() {
	// Создание локальной переменной типа Base
	Base local;
	// Возврат указателя на локальную переменную
	return &local;
}

// Объявление функции func3, которая возвращает ссылку на объект класса Base
// В данном случае создаётся статический объект, который будет жить до конца работы программы. При каждом вызове функции будет
// возвращаться ссылка на этот объект. Это позволяет избежать проблем с утечками памяти, но может привести к проблемам с многопоточностью.
Base& func3() {
	// Создание локальной переменной типа Base
	Base local;
	// Возврат ссылки на локальную переменную
	return local;
}

// Объявление функции func4, которая возвращает объект класса Base, созданный в куче
// В данном случае создаётся объект в куче, и возвращается копия этого объекта. Это позволяет избежать проблем с многопоточностью,
// но может привести к утечкам памяти, если не будет вызван оператор delete для освобождения памяти.
Base func4() {
	// Создание указателя на объект класса Base в куче
	Base* local = new Base();
	// Возврат объекта, на который указывает указатель
	return *local;
}

// Объявление функции func5, которая возвращает указатель на объект класса Base, созданный в куче
// В данном случае создаётся объект в куче, и возвращается указатель на него. Это позволяет избежать проблем с многопоточностью,
// но может привести к утечкам памяти, если не будет вызван оператор delete для освобождения памяти.

Base* func5() {
	// Создание указателя на объект класса Base в куче
	Base* local = new Base();
	// Возврат указателя на созданный объект
	return local;
}

// Объявление функции func6, которая возвращает ссылку на объект класса Base, созданный в куче
// В данном случае создаётся объект в куче, и возвращается ссылка на него. Это позволяет избежать проблем с многопоточностью,
// но может привести к утечкам памяти, если не будет вызван оператор delete для освобождения памяти. Кроме того, в данном случае
// возвращается ссылка на объект, который может быть удалён из памяти, что приведёт к неопределённому поведению программы.
Base& func6() {
	// Создание указателя на объект класса Base в куче
	Base* local = new Base();
	// Возврат ссылки на объект, на который указывает указатель
	return *local;
}
int main() {
	srand(time(0));
	cout << "1)\n{\n";//жизненный цикл unique_ptr
	cout << "unique_ptr<Base> basa(new Base())" << endl;
	{
		unique_ptr <Base> basa(new Base());
	}
	cout << "}\n";
	cout << "2)\n{\n";//жизненный цикл shared_ptr
	cout << "std::shared_ptr<Base> basa(new Base())" << endl;
	{
		shared_ptr <Base> basa(new Base());
		{
			shared_ptr<Base> basa1=basa;
			cout << basa << endl << basa1<< endl;
		}
	}
	cout << "}\n";
	cout << "3)\n{\n";//небезопасное и безопасное приведение типов
	{
		int dc=0, sc = 0;
		Base* obej[4];
		for (int i = 0; i < 4; i++) {
			if (i % 2)
				obej[i] = new Desk;
			else
				obej[i] = new SonDesk;
		}
		for (int i = 0; i < 4; i++) {
			if (i % 2) {
				Desk* c = dynamic_cast<Desk*>(obej[i]);
				if (c != nullptr) {
					dc++;
					cout << c->test() << endl;
				}
				else {
					SonDesk *a = dynamic_cast<SonDesk*>(obej[i]);
					if (a != nullptr) {
						dc++;
						cout << a->test() << endl;
					}
				}
			}
			else {	
				if (obej[i]->IsA("Desk")) {
					sc++;
					cout << static_cast<Desk*>(obej[i])->test() << endl;
				}
				if (obej[i]->IsA("SonDesk")) {
					sc++;
					cout << static_cast<SonDesk*>(obej[i])->test() << endl;
				}
				
			}
		}
		cout << "dc: " << dc << endl;
		cout << "sc: " << sc << endl;
	}
	cout << "}\n";
	cout << "4)\n{\n";//вызов виртуальных и невиртуальных методов в дочернем объекте
	{
		Desk testDaughter;
		cout << "Result of Desk::doSomething1() and non virtual method2: " << endl;
		testDaughter.doSomething1();
		cout << "Result of Desk::doSomething1() and virtual method2: " << endl;
		testDaughter.doSomething2();
	}
	cout << "}\n";
	cout << "5)\n{\n";//передача объектов в качестве параметров
	{
		unique_ptr <Base> test(new Desk());
		func(*test);
		func(test.get());
	}
	cout << "}\n";
	cout << "6)\n{\n";//возврат созданных в функциях объектов
	{
		cout << "func1():\n";
		Base b1;
		b1 = func1();
		
		cout << "func2():\n";
		Base *b2;
		b2 = func2();
		
		cout << "func3():\n";
		Base& b3=func3();
		
		cout << "func4():\n";
		Base b4;
		b4 = func4();
		
		cout << "func5():\n";
		Base *b5;
		b5 = func5();
		
		cout << "func6():\n";
		Base& b6=func6();
		
	}
	cout << "}\n";
	return 0;
}