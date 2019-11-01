#ifndef STATUSPASER_H
#define STATUSPASER_H

#include "statusmonitor.h"
#include "error.h"

class StatusPaser
{
public:
    StatusPaser();

    static bool AnyTonerReachLevel1(const PrinterStatus_struct& m_PrinterStatus);
    static bool IsNonDellTonerMode(const PrinterStatus_struct& m_PrinterStatus);
    static bool OnlyColorTonerEmpty(const PrinterStatus_struct& m_PrinterStatus);
};

extern int usb_error_printing;
extern int usb_error_scanning;
extern int usb_error_usb_locked;
extern int usb_error_busy;
#endif // STATUSPASER_H
