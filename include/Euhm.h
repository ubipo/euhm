/*
MS HRESULT Adaptation

Format:
0000000000000000000000000000000
0...                      ...31

Bit Nbr: Name - 0 - 1
31: Severity - OK - FAIL
30: ?
29: 1
28: ?
27-16 (12 bit): Facility / system ID
11-0  (16 bit): Status Code
OR
27-16 (12 bit): Facility / system ID
15-8  (8  bit): Subsystem
7-0   (8  bit): Short Status code

0x???????4 OK
0x???????5 FAIL

Ex:
0xE501FFA5 Fail in System FFA, Subsystem 01, Code E5
*/

#define MSK_SEVERITY 0x1
#define MSK_MSHRCERR 0x4 // MicroSoft HResult Custom Error
#define MSK_FACILITY 0xFFF0
#define MSK_STATUS 0xFFFF0000
#define MSK_SUBSYSTEM 0xFF0000
#define MSK_SSTATUS 0xFF000000 // Short Status

#define ERR(severity, facility, status) (severity | MSK_MSHRCERR | (facility << 4) | (status << 16))
#define ERRS(severity, facility, subsystem, sstatus) (severity | MSK_MSHRCERR | (facility << 4) | (subsystem << 16) | (sstatus << 24))
#define ERR_OK 0x0
#define ERR_SUCCESS 0x0
#define ERR_FAIL 0x1

#define GET_SEVERITY(code) (code & MSK_SEVERITY)
#define GET_FACILITY(code) ((code & MSK_FACILITY) >> 4)
#define GET_STATUS(code) ((code & MSK_STATUS) >> 16)
#define GET_SUBSYSTEM(code) ((code & MSK_SUBSYSTEM) >> 16)
#define GET_SSTATUS(code) ((code & MSK_SSTATUS) >> 24)

#define SUCCESSFUL(code) ((code & MSK_SEVERITY) == ERR_OK)
#define FAILED(code) ((code & MSK_SEVERITY) != ERR_OK)
#define CHK_S(code) ((code & MSK_SEVERITY) == ERR_OK)
#define CHK_F(code) ((code & MSK_SEVERITY) != ERR_OK)


/*
  Serial.println(SUCCESSFUL(ERR_OK));
  Serial.println(SUCCESSFUL(ERR_FAIL));
  Serial.println(FAILED(ERR_OK));
  Serial.println(FAILED(ERR_FAIL));
  Serial.println(0xE501FFA5, HEX);
  Serial.println(ERRS(1, 0xFFA, 1, 0xE5), HEX);
  Serial.println(ERR(1, 0xFFA, 0xE501), HEX);
  Serial.println(GET_SEVERITY(0xE501FFA5), HEX);
  Serial.println(GET_FACILITY(0xE501FFA5), HEX);
  Serial.println(GET_STATUS(0xE501FFA5), HEX);
  Serial.println(GET_SUBSYSTEM(0xE501FFA5), HEX);
  Serial.println(GET_SSTATUS(0xE501FFA5), HEX);
*/