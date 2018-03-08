#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define PI acos(-1.0)
#define eps 1e-15
typedef double Type;

// ��ֵ����
int threeValue(Type d) {
    if(fabs(d) < 1e-6)
		return 0;
	return d > 0 ? 1 : -1;
}

class Point3D {
    Type x, y, z;

public:
	Point3D(){
	}
	Point3D(Type _x, Type _y, Type _z): x(_x), y(_y), z(_z) {}
	void read() {
		scanf("%lf %lf", &x, &y);
		z = 0;
		//scanf("%lf %lf %lf", &x, &y, &z);
	}
	void print() {
		printf("<x=%lf, y=%lf, z=%lf>\n", x, y, z);
	}
	inline Type getx() { return x; }
	inline Type gety() { return y; }
	inline Type getz() { return z; }
	bool inRange(Point3D& max) const;
	Point3D operator+(const Point3D& other) const;
	Point3D operator-(const Point3D& other) const;
	Point3D operator*(const double &k) const;
	Point3D operator/(const double &k) const;
	Type operator*(const Point3D& other) const;
	double len();
	Point3D normalize();
};

typedef Point3D Vector3D;

double Vector3D::len() {
	return sqrt(x*x + y*y + z*z);
}

Point3D Vector3D::normalize() {
	double l = len();
	if(threeValue(l)) {
		x /= l;
		y /= l;
		z /= l;
	}
	return *this;
}

bool Point3D::inRange(Point3D& max) const {
	return (0<=x&&x<=max.x) && (0<=y&&y<=max.y) && (0<=z&&z<=max.z);
}

Point3D Point3D::operator+(const Point3D& other) const {
	return Point3D(x + other.x, y + other.y, z + other.z);
}

Point3D Point3D::operator-(const Point3D& other) const {
	return Point3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator *(const double &k) const {
    return Point3D(x * k, y * k, z * k);
}

Point3D Point3D::operator /(const double &k) const {
    return (*this) * (1/k);
}

Type Point3D::operator*(const Point3D& other) const {
	return x*other.x + y*other.y + z*other.z;
}


#define MAXN 1010
#define MAXC 1000
#define INF 1000000000.0

struct Point3DSet {
	int n;
	Point3D p[MAXN];
};

/*
	ģ���˻�-ģ��
	��Զ���������
*/
class simulatedAnnealing {
	// ��̬����ͣ��¶�
	static const double minTemperature;
	// �¶��½���
	static const double deltaTemperature;
	// ���к�ѡ�����
	static const int solutionCount;
	// ÿ����ĵ�������
	static const int candidateCount;
private:
	Point3D bound;
	Point3D x[MAXC];
	Point3DSet pointSet;
	double temperature;

	bool valid(const Point3D& pt);
	double randIn01();
	double evaluateFunc(const Point3D& pt);
	Point3D getRandomPoint();
	Vector3D getRandomDirection();
	Point3D getNext(const Point3D& now);
public:
	void start(double T, Point3D B, Point3DSet& pointSet);
	Point3D getSolution();
	static simulatedAnnealing& Instance();
};

// �ĸ���������
// ��̬����ͣ��¶�
const double simulatedAnnealing::minTemperature = 1e-2;
// �¶��½���
const double simulatedAnnealing::deltaTemperature = 0.95;
// ���к�ѡ�����
const int simulatedAnnealing::solutionCount = 10;
// ÿ����ĵ�������
const int simulatedAnnealing::candidateCount = 30;

bool simulatedAnnealing::valid(const Point3D& pt) {
	return pt.inRange(bound);
}

double simulatedAnnealing::randIn01() {
	return (rand() + 0.0) / RAND_MAX;
}

/*
	���ۺ�������ֵԽСԽ��
	��ͬ���⣬����ֻ��Ҫ�޸Ĺ��ۺ���������� ��Զ���������
*/
double simulatedAnnealing::evaluateFunc(const Point3D& pt) {
	// TODO
	// ��С���� Խ��Խ�ţ����Թ�ֵȡ�෴��
	double minDist = INF;
	for(int i = 0; i < pointSet.n; ++i) {
		double dist = (pointSet.p[i] - pt).len();
		if(dist < minDist) 
			minDist = dist;
	}
	return - minDist;
}

/*
	���һ��[0 - bound]�ĵ㣬���Ҫ���и����㣬�뽫�������������ƽ��
*/
Point3D simulatedAnnealing::getRandomPoint() {
	return Point3D(bound.getx() * randIn01(), bound.gety() * randIn01(), 0);//bound.getz() * randIn01());
}

/*
	���һ������ע�ⷽ��������κη��򣬱����˸���
*/
Vector3D simulatedAnnealing::getRandomDirection() {
	Vector3D v(randIn01()-0.5, randIn01()-0.5, 0);//randIn01()-0.5);
	return v.normalize();
}

Point3D simulatedAnnealing::getNext(const Point3D& now) {
	return now + getRandomDirection() * temperature;
}

/*
  ģ���˻�
*/
void simulatedAnnealing::start(double T, Point3D B, Point3DSet& PS) {
	// 0.��ʼ���¶�
	temperature = T;
	bound = B;
	pointSet = PS;
	int i, j;

	// 1.�������solutionCount����ʼ��
	for(i = 0; i < solutionCount; ++i) {
		x[i] = getRandomPoint();
	}

	while (temperature > minTemperature) {
		// 2.��ÿ����ǰ��������Ż�ѡ��
		for(i = 0; i < solutionCount; ++i) {
			double nextEval = INF;
			Point3D nextOpt;
			// 3.����ÿ����ǰ�⣬���ѡȡ������candidateCount���㣬���ҽ����ŵ��Ǹ��Ᵽ��
			for(j = 0; j < candidateCount; ++j) {
				Point3D next = getNext(x[i]);
				if(!valid(next)) {
					continue;
				}
				double Eval = evaluateFunc(next);
				if(Eval < nextEval) {
					nextEval = Eval;
					nextOpt = next;
				}
			}

			// 4.û�����ɿ��н�
			if(nextEval >= INF)
				continue;

			// 5.�������ɵ����Ž��ԭ���Ľ���бȽ�
			double deltaEval = evaluateFunc(nextOpt) - evaluateFunc(x[i]);
			if(deltaEval < 0) {
				// 6.��ԭ���Ľ���ţ�ֱ���滻
				x[i] = nextOpt;
			}else {
				// 7.û��ԭ���Ľ��ţ�����һ�����ʽ��н���
				// ����������޻�Խ��ԽС��ֱ�����������0
				if( randIn01() < exp(-deltaEval/temperature) ) {
					x[i] = nextOpt;
				}	
			}
		}
		temperature *= deltaTemperature;
	}
	//for(i = 0; i < solutionCount; ++i) x[i].print();
}

Point3D simulatedAnnealing::getSolution() {
	int retIdx = 0;
	for (int i = 1; i < solutionCount; ++i) {
		if(evaluateFunc(x[i]) < evaluateFunc(x[retIdx])) {
			retIdx = i;
		}
	}
	return x[retIdx];
}

simulatedAnnealing& simulatedAnnealing::Instance() {
	static simulatedAnnealing inst;
	return inst;
}
