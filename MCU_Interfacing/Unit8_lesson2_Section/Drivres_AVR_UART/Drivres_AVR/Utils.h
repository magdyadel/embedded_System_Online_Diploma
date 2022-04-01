/*
 * Utils.h
 *
 * Created: 3/20/2022 4:07:52 PM
 *  Author: MAGDY
 */ 


#ifndef UTILS_H_
#define UTILS_H_

// set bit to 1
#define SETBIT(reg, bit)         (reg |= (1<<bit))

// clear bit to 0
#define CLEARBIT(reg, bit)       (reg &= ~(1<<bit))

// read bit digital value ( 1 or 0 )
#define READBIT(reg, bit)        ((reg>>bit) & 1)

#define TOGGLEBIT(reg, bit)      (reg ^= (1<<bit))




#endif /* UTILS_H_ */