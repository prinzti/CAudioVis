#ifndef VISOUTPUTDATA_H_
#define VISOUTPUTDATA_H_

struct UnitData {
	bool red;
	bool green;
	bool blue;
};

struct VisOutputData {
	UnitData left;
	UnitData centerLeft;
	UnitData centerRight;
	UnitData right;
	UnitData bottom;
};

#endif /* VISOUTPUTDATA_H_ */