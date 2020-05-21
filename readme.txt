
옵션 설명
1. -t 1000
runningTime = 1000; (default)

2. -s 12500
samplingRate = 12500; (default)

3. -p tsc
priority = "tsc"; (default)
tcs stc sct cts cst 사용가능

t : timestep (60개의 샘플)
s : stream (포트 04사용시 2개)
c : channel (32채널)

4. -P 04
dataStreams = "04"; (default)
0: portA1 (32ch)
1: portB1 (32ch)
4: port A2 (32ch)
5: port B2 (32ch)


실행예시
.\intan.exe 
.\intan.exe -t 1000 -s 12500

