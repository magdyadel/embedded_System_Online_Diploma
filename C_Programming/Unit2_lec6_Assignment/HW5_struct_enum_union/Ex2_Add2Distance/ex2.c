#include <stdio.h>

struct SDistance ReadData();
void addDistance(struct SDistance d1, struct SDistance d2);

struct SDistance {
    int m_feet;
    float m_inch;
};

struct SDistance ReadData(){
    struct SDistance dist;
    static int i =0;
    printf("\nEnter information for %dnd distance\n",++i);
    printf("Enter feet: ");
	scanf("%d", &dist.m_feet);

	printf("Enter inch: ");
	scanf("%f", &dist.m_inch);

	return dist;	
}

void addDistance(struct SDistance d1, struct SDistance d2){
    struct SDistance result;
    result.m_feet = d1.m_feet + d2.m_feet;
    result.m_inch = d1.m_inch + d2.m_inch;
    
    while (result.m_inch >= 12.0) {
        result.m_inch = result.m_inch - 12.0;
        ++result.m_feet;
    }
    printf("\nSum of distances = %d\'-%.1f\"", result.m_feet, result.m_inch);
}
int main()
{
    struct SDistance dist1,dist2; 
    dist1 = ReadData();
	dist2 = ReadData();
    
    addDistance(dist1,dist2);
    return 0;
}
