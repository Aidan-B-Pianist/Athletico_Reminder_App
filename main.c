#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main(void) {
    HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);
    if(!timer) return 1;

    LARGE_INTEGER due;
    due.QuadPart = -300LL * 10000000LL;

    LONG period_ms = 4 * 60 * 60 * 1000; // 6 hours

    if(!SetWaitableTimer(timer, &due, period_ms, NULL, NULL, FALSE)) {
        CloseHandle(timer);
        return 1;
    }

    for(;;) {
        DWORD w = WaitForSingleObject(timer, INFINITE);
        if (w != WAIT_OBJECT_0) break;
        
        MessageBox(NULL, "Do your atheltico exercises!", "Daily Reminder", MB_OK | MB_ICONINFORMATION);
    }

    CloseHandle(timer);
    return 0;
}