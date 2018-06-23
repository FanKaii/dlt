#include "dlt.h"
#include <vector>

class Distance
{
public:
	size_t idex1;
	size_t idex2;

	double dis;
};

void storagePts(const std::shared_ptr<std::vector<DLT::Point3D>> &, const std::string &);
void storageDis(const std::vector<Distance> &, const std::string &);
std::vector<Distance> getDistances(const std::shared_ptr<std::vector<DLT::Point3D>> &);

int main()
{
	DLT dlt;

	DLT::Model m_l = dlt.sloveModel("���Ƶ�.txt", "�����.txt", true, "����Ƭ������.txt");
	DLT::Model m_r = dlt.sloveModel("���Ƶ�.txt", "�����.txt", true, "����Ƭ������.txt");

	std::cout << "����Ƭ��������" << std::endl;
	m_l.print();
	std::cout << "����Ƭ��������" << std::endl;
	m_r.print();

	std::shared_ptr<std::vector<DLT::Point3D>> pts;
	pts = dlt.compute("�������.txt", "�������.txt", m_l, m_r);
	storagePts(pts, "�﷽�������.txt");

	std::vector<Distance> ds = getDistances(pts);
	storageDis(ds, "��֮��ľ���.txt");

	system("pause");
	return 0;
}

void storagePts(const std::shared_ptr<std::vector<DLT::Point3D>> &pts, const std::string &file)
{
	std::fstream fout(file, std::ios::out);
	if (!fout)
		return;

	for (auto it = pts->begin(); it != pts->end(); ++it)
		fout << std::fixed << std::setprecision(3) << it->idex << "   " << it->getX() << "   " << it->getY() << "   " << it->getZ() << std::endl;
}

void storageDis(const std::vector<Distance> &ds, const std::string &file)
{
	std::fstream fout(file, std::ios::out);
	if (!fout)
		return;

	for (auto it = ds.begin(); it != ds.end(); ++it)
		fout << std::fixed << std::setprecision(3) << it->idex1 << "   " << it->idex2 << "   " << it->dis << std::endl;
}

std::vector<Distance> getDistances(const std::shared_ptr<std::vector<DLT::Point3D>> &pts)
{
	std::vector<Distance> ds;
	for (auto i = pts->cbegin(); i != pts->cend(); ++i)
		for (auto j = i + 1; j != pts->cend(); ++j)
		{
			double d = sqrt((i->getX() - j->getX())*(i->getX() - j->getX()) + (i->getY() - j->getY())*(i->getY() - j->getY()) + (i->getZ() - j->getZ())*(i->getZ() - j->getZ()));
		
			Distance dis = { i->idex,j->idex,d };
			ds.push_back(dis);
		}

	return ds;
}