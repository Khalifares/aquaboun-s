//#define DEBUG // à commenter pour enlever le debug

#ifdef DEBUG
#define DPRINTF(s)   {Serial.print(F(s));}
#define DPRINT(x)  {Serial.print(x);}
#define DPRINTLN(x)  {Serial.println(x);}
#else
#define DPRINTF(s)
#define DPRINT(x)
#define DPRINTLN(x)

#endif
