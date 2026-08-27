#import <stdio.h>
#import <Foundation/Foundation.h>

@interface Fraction : NSObject
{
    int numerator;
    int denominator;
}

-(int) numerator;
-(int) denominator;
-(void) setNumerator: (int) num;
-(void) setDenominator: (int) denom;
-(void) print;

@end

@implementation Fraction

-(int) numerator
{
    return numerator;
}

-(int) denominator
{
    return denominator;
}

- (void) setNumerator: (int) num
{
    numerator = num;
}

-(void) setDenominator: (int) denom
{
    denominator = denom;
}

-(void) print
{
    printf ("The value of the fraction is %i/%i\n", numerator, denominator);
}

@end

int main (void)
{
    Fraction *myFract;

    myFract = [[Fraction alloc] init];

    [myFract setNumerator: 1];
    [myFract setDenominator: 3];

    printf ("The numerator is %i, and the denominator is %i\n", [myFract numerator], [myFract denominator]);

    [myFract print];

    [myFract release];

    return 0;
}




