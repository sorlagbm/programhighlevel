#include "queue.h"

Queue::Queue(int i, FileWork* _curFile, QTableWidget* _curWid, size_t _q_rows):
    _queue(i), curFile(_curFile), curWid(_curWid), q_rows(_q_rows) {}
