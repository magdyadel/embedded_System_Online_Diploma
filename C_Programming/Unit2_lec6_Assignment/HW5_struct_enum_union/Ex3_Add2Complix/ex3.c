#include <stdio.h>

struct SComplix ReadData();
void addComplix(struct SComplix c1, struct SComplix c2);

struct SComplix {
    float m_Real;
    float m_Imaginary;
};

struct SComplix ReadData(){
    struct SComplix c;
    static int i =0;
    printf("\nFor %dnd Complix number\n",++i);
	printf("Enter real and imaginary respectively: ");
	scanf("%f %f", &c.m_Real, &c.m_Imaginary);

	return c;	
}

void addComplix(struct SComplix c1, struct SComplix c2){
    struct SComplix result;
    result.m_Real = c1.m_Real + c2.m_Real;
    result.m_Imaginary = c1.m_Imaginary + c2.m_Imaginary;
    
    printf("Sum = %.1f+%.1fi", result.m_Real, result.m_Imaginary);
}

int main()
{
    struct SComplix c1,c2; 
    c1 = ReadData();
	c2 = ReadData();
    
    addComplix(c1,c2);
    return 0;
}
