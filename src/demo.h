#ifndef DEMO_H
#define DEMO_H

typedef void (*DemoFunc)(void);

typedef struct
{
    const char *flag;
    DemoFunc run;
} Demo;

int run_demo(const char *arg);

#endif