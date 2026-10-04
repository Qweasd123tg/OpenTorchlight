#ifndef IRANDOMWEIGHT_H
#define IRANDOMWEIGHT_H
class iRandomWeight
{
public:
    virtual ~iRandomWeight();
    virtual unsigned int GetRandomWeight() = 0;
    virtual void SetRandomWeight(unsigned int weight) = 0;
};
#endif
