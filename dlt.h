#ifndef DLT_H_
#define DLT_H_

#include <opencv.hpp>
#include <ostream>
#include <memory>
#include <random>

class DLT
{
public:
	/*
	* ��liϵ��������ϵ����x0,y0��ɵ���Ƭģ��
	*/
	class Model
	{
	public:
		Model() = default;
		Model(double *l, double k1, double k2, double p1, double p2, double x0, double y0) :m_k1(k1), m_k2(k2), m_p1(p1), m_p2(p2), m_x0(x0), m_y0(y0)
		{
			for (int i = 0; i < 11; ++i)
				m_l[i] = l[i];
		}
		Model(const cv::Mat_<double> &l, double k1, double k2, double p1, double p2, double x0, double y0) :m_k1(k1), m_k2(k2), m_p1(p1), m_p2(p2), m_x0(x0), m_y0(y0)
		{
			for (int i = 0; i < 11; ++i)
				m_l[i] = l.at<double>(i, 0);
		}

		void print()const;
		void storage(const std::string &file)const;

		double m_l[11]{ 0 };
		double m_k1, m_k2, m_p1, m_p2;
		double m_x0, m_y0;

	private:
		void display(std::ostream &)const;
	};

	/*
	* �﷽������
	*/
	class Point3D
	{
	public:
		Point3D() = default;
		Point3D(size_t idex, double X, double Y, double Z) :idex(idex), m_X(X), m_Y(Y), m_Z(Z) {}

		size_t idex;

		double getX()const { return m_X; }
		double getY()const { return m_Y; }
		double getZ()const { return m_Z; }
	private:
		double m_X = 0;
		double m_Y = 0;
		double m_Z = 0;
	};
	
	//����ļ���֯��Ϊ����n�У���һ�е�id���Ϳ��Ƶ��Ӧ��,�ڶ���x,������y
	//���Ƶ��ļ���֯��Ϊ����n�У���һ�е�id��������Ӧ�����ڶ���X��������Y��������Z

	/*
	* ������Ƭģ��
	*/
	Model sloveModel(const std::string &fileCPs, const std::string &fileIPs, bool storageRes = false, const std::string &file = std::string())const;

	/*
	* �����﷽�����ֻ֧꣬�ֵ���������Լ���
	*/
	std::shared_ptr<std::vector<Point3D>> compute(const std::string &imgPointsfile_l, const std::string &imgPointsfile_r, const Model &m_l, const Model &m_r)const;
private:
	/*
    * ͼ�������
	*/
	class Point2D
	{
	public:
		Point2D() = default;
		Point2D(size_t idex, float x, float y) :idex(idex), x(x), y(y) {}

		float x, y;
		size_t idex;
	};

	bool importControlPoints(const std::string &, std::vector<Point3D> &)const;
	bool importImagePoints(const std::string &,std::vector<Point2D> &)const;

	//Liϵ�����ƽ���
	void approximateCalculateLi(const std::vector<Point2D> &, const std::vector<Point3D> &, Model &)const;
	//Liϵ����ȷ����
	void accurateCalculateLi(const std::vector<Point2D> &, const std::vector<Point3D> &, Model &)const;

	//�﷽��������ƽ���
	void approximateCalculatePts(const std::vector<Point2D> &, const std::vector<Point2D> &, const Model &, const Model &, std::vector<Point3D> &)const;
	//�﷽�����꾫ȷ����
	void accurateCalculatePts(const std::vector<Point2D> &, const std::vector<Point2D> &, const Model &, const Model &, std::vector<Point3D> &)const;
};

#endif