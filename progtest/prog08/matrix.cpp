#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCell {
    struct TCell *m_Right;
    struct TCell *m_Down;
    int m_Row;
    int m_Col;
    int m_Data;
} TCELL;

typedef struct TRowCol {
    struct TRowCol *m_Next;
    TCELL *m_Cells;
    int m_Idx;
} TROWCOL;

typedef struct TSparseMatrix {
    TROWCOL *m_Rows;
    TROWCOL *m_Cols;
} TSPARSEMATRIX;


#endif /* __PROGTEST__ */
//---------------------------------------------------------------------------------------------------------------------//
TROWCOL * initRowCol ( int idx)
{
    auto * rowCol = (TROWCOL *) malloc (sizeof (TROWCOL));
    if(!rowCol) return rowCol;

    rowCol->m_Cells = nullptr;
    rowCol->m_Idx = idx;
    rowCol->m_Next = nullptr;

    return rowCol;
}

TROWCOL * insertRowCol (TROWCOL ** root, int idx)
{
    TROWCOL * current = *root;
    TROWCOL * prev = nullptr;

    if(current) {
        while (current && (current->m_Idx <= idx)) {
            if (current->m_Idx == idx) return current;
            prev = current;
            current = current->m_Next;
        }
    }

    auto * newRowCol = initRowCol(idx);
    //if(!newRowCol) return nullptr;

    newRowCol->m_Next = current;
    ( prev ? prev->m_Next : *root) = newRowCol;

    return newRowCol;
}


bool findRowCol (TROWCOL ** current, TROWCOL ** prev, int idx)
{
    if(!*current) return false;
    while (*current   && (*current)->m_Idx <= idx) {
        if ((*current)->m_Idx == idx) {
            return true;
        }
        *prev = *current;
        *current = (*current)->m_Next;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------------------------//

TCELL * initCell(int row, int col, int data) {
    auto cell = (TCELL * ) malloc(sizeof(TCELL));
    if (!cell) return nullptr;
    cell->m_Right = nullptr;
    cell->m_Down = nullptr;
    cell->m_Row = row;
    cell->m_Col = col;
    cell->m_Data = data;
    return cell;
}


TCELL * insertCellRow(TROWCOL * row,  int rowIdx, int colIdx, int data)
{
    TCELL * current = row->m_Cells;
    TCELL * prev = nullptr;

    if(current){
    while (current && current->m_Col <= colIdx)
    {
        if (current->m_Col == colIdx)
        {
            current->m_Data = data;
            return current;
        }
        prev = current;
        current =  current->m_Right;
    }}

    auto cell = initCell(rowIdx,colIdx,data);
    if(!cell) return cell;

    cell->m_Right = current;
    (prev ? prev->m_Right : row->m_Cells) = cell;

    return cell;
}

void  insertCellCol(TROWCOL * col, TCELL * cell, int rowIdx)
{

    TCELL * current = col->m_Cells;
    TCELL * prev = nullptr;

    if(current) {
        while (current && current->m_Col <= rowIdx) {
            if (current->m_Col == rowIdx) return;

            prev = current;
            current = current->m_Down;
        }
    }
    cell->m_Down = current;
    (prev ? prev->m_Down : col->m_Cells) = cell;
}



TCELL * removeCellRow(TROWCOL *row, int rowIdx,  int colIdx){
    TCELL * current = row->m_Cells;
    TCELL * prev = nullptr;
    if(!current) return nullptr;

    while (current && !(current->m_Col == colIdx && current->m_Row == rowIdx)){
        prev = current;
        current =  current->m_Right;
    }
    if (current) (prev ? prev->m_Right : row->m_Cells) = current->m_Right;
    return current;
}

TCELL *removeCellCol(TROWCOL *col, int rowIdx,  int colIdx) {
    TCELL * current = col->m_Cells;
    TCELL * prev = nullptr;
    if(!current) return nullptr;

    while (current && !(current->m_Col == colIdx && current->m_Row == rowIdx)){
        prev = current;
        current =  current->m_Down;
    }
    if (current) (prev ? prev->m_Down : col->m_Cells) = current->m_Down;
    return current;
}

void freeCell (TCELL ** cell)
{
    (*cell)->m_Down = nullptr;

    (*cell)->m_Row = -1;
    (*cell)->m_Col = -1;
    (*cell)->m_Data = -1;

    free (*cell);
    *cell = NULL;

}
//---------------------------------------------------------------------------------------------------------------------//
void initMatrix(TSPARSEMATRIX *m) {
    m->m_Rows = nullptr;
    m->m_Cols = nullptr;
}


void freeRow(TROWCOL ** rowCol)
{
    auto cell = (*rowCol)->m_Cells;
    while (cell)
    {
        TCELL * current = cell;
        cell = cell->m_Right;
        freeCell(&current);
    }
    (*rowCol)->m_Cells = nullptr;
    TROWCOL *temp = *rowCol;
    *rowCol = nullptr;
    free(temp);
}
void freeColumn(TROWCOL ** rowCol)
{
    TROWCOL *temp = *rowCol;
    *rowCol = nullptr;
    free(temp);
}


void freeRows (TROWCOL ** rowCol)
{
    if (!*rowCol) return;
    freeRows(&(*rowCol)->m_Next);
    freeRow(rowCol);

}

void freeColumns (TROWCOL ** rowCol)
{
    if (!*rowCol) return;
    freeColumns(&(*rowCol)->m_Next);
    freeColumn(rowCol);
}

void freeMatrix(TSPARSEMATRIX *m) {
    freeRows(&m->m_Rows);
    freeColumns(&m->m_Cols);
}

//---------------------------------------------------------------------------------------------------------------------//
void addSetCell(TSPARSEMATRIX *m,
                int rowIdx,
                int colIdx,
                int data) {

   // if(colIdx < 0 || rowIdx < 0) return;

    TROWCOL * currentRow = insertRowCol(&m->m_Rows, rowIdx);
    TROWCOL * currentColumn = insertRowCol(&m->m_Cols, colIdx);

    TCELL * cell = insertCellRow(currentRow, rowIdx, colIdx, data);
 //   if(!cell) return;
    insertCellCol(currentColumn, cell, rowIdx);

}

bool removeCell(TSPARSEMATRIX *m,
                int rowIdx,
                int colIdx) {

    //if(colIdx < 0 || rowIdx < 0) return false;

    TROWCOL * prevRow = nullptr;
    TROWCOL * prevCol = nullptr;

    TROWCOL * currentRow = m->m_Rows;
    TROWCOL * currentCol = m->m_Cols;

    if (!findRowCol( &currentRow,&prevRow, rowIdx)
        || !findRowCol(&currentCol,&prevCol, colIdx)) return false;

    TCELL * cellToRemove = removeCellRow(currentRow , rowIdx, colIdx);
    if(!cellToRemove || !removeCellCol(currentCol, rowIdx, colIdx)) return false;

    if(!currentRow->m_Cells)
    {
        (prevRow ? prevRow->m_Next : m->m_Rows) = currentRow->m_Next;
        freeRow(&currentRow);
    }

    if(!currentCol->m_Cells)
    {
        (prevCol ? prevCol->m_Next : m->m_Cols)  = currentCol->m_Next;
        freeColumn(&currentCol);
    }

    freeCell(&cellToRemove);
    return true;
}



//---------------------------------------------------------------------------------------------------------------------//
#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TSPARSEMATRIX m;

    initMatrix(&m);
    addSetCell(&m, 0, 1, 10);
    removeCell(&m, 0, 1);

       addSetCell(&m, 0, 1, 10);
    addSetCell(&m, 1, 0, 20);
    addSetCell(&m, 1, 5, 30);
    addSetCell(&m, 2, 1, 40);

      // addSetCell(&m, 2, 1, 50);
    assert (m.m_Rows
            && m.m_Rows->m_Idx == 0
            && m.m_Rows->m_Cells
            && m.m_Rows->m_Cells->m_Row == 0
            && m.m_Rows->m_Cells->m_Col == 1
            && m.m_Rows->m_Cells->m_Data == 10
            && m.m_Rows->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next
            && m.m_Rows->m_Next->m_Idx == 1
            && m.m_Rows->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Cells->m_Row == 1
            && m.m_Rows->m_Next->m_Cells->m_Col == 0
            && m.m_Rows->m_Next->m_Cells->m_Data == 20
            && m.m_Rows->m_Next->m_Cells->m_Right
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Row == 1
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Col == 5
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Data == 30
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next
            && m.m_Rows->m_Next->m_Next->m_Idx == 2
            && m.m_Rows->m_Next->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Row == 2
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Col == 1
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Data == 40
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Cols
            && m.m_Cols->m_Idx == 0
            && m.m_Cols->m_Cells
            && m.m_Cols->m_Cells->m_Row == 1
            && m.m_Cols->m_Cells->m_Col == 0
            && m.m_Cols->m_Cells->m_Data == 20
            && m.m_Cols->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next
            && m.m_Cols->m_Next->m_Idx == 1
            && m.m_Cols->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Cells->m_Row == 0
            && m.m_Cols->m_Next->m_Cells->m_Col == 1
            && m.m_Cols->m_Next->m_Cells->m_Data == 10
            && m.m_Cols->m_Next->m_Cells->m_Down
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Row == 2
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Col == 1
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Data == 40
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next
            && m.m_Cols->m_Next->m_Next->m_Idx == 5
            && m.m_Cols->m_Next->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Row == 1
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Col == 5
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Data == 30
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Rows->m_Cells == m.m_Cols->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Cells == m.m_Cols->m_Cells);
    assert (m.m_Rows->m_Next->m_Cells->m_Right == m.m_Cols->m_Next->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Next->m_Cells == m.m_Cols->m_Next->m_Cells->m_Down);
    addSetCell(&m, 230, 190, 50);
    assert (m.m_Rows
            && m.m_Rows->m_Idx == 0
            && m.m_Rows->m_Cells
            && m.m_Rows->m_Cells->m_Row == 0
            && m.m_Rows->m_Cells->m_Col == 1
            && m.m_Rows->m_Cells->m_Data == 10
            && m.m_Rows->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next
            && m.m_Rows->m_Next->m_Idx == 1
            && m.m_Rows->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Cells->m_Row == 1
            && m.m_Rows->m_Next->m_Cells->m_Col == 0
            && m.m_Rows->m_Next->m_Cells->m_Data == 20
            && m.m_Rows->m_Next->m_Cells->m_Right
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Row == 1
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Col == 5
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Data == 30
            && m.m_Rows->m_Next->m_Cells->m_Right->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next
            && m.m_Rows->m_Next->m_Next->m_Idx == 2
            && m.m_Rows->m_Next->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Row == 2
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Col == 1
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Data == 40
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next->m_Next
            && m.m_Rows->m_Next->m_Next->m_Next->m_Idx == 230
            && m.m_Rows->m_Next->m_Next->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Next->m_Next->m_Cells->m_Row == 230
            && m.m_Rows->m_Next->m_Next->m_Next->m_Cells->m_Col == 190
            && m.m_Rows->m_Next->m_Next->m_Next->m_Cells->m_Data == 50
            && m.m_Rows->m_Next->m_Next->m_Next->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Cols
            && m.m_Cols->m_Idx == 0
            && m.m_Cols->m_Cells
            && m.m_Cols->m_Cells->m_Row == 1
            && m.m_Cols->m_Cells->m_Col == 0
            && m.m_Cols->m_Cells->m_Data == 20
            && m.m_Cols->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next
            && m.m_Cols->m_Next->m_Idx == 1
            && m.m_Cols->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Cells->m_Row == 0
            && m.m_Cols->m_Next->m_Cells->m_Col == 1
            && m.m_Cols->m_Next->m_Cells->m_Data == 10
            && m.m_Cols->m_Next->m_Cells->m_Down
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Row == 2
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Col == 1
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Data == 40
            && m.m_Cols->m_Next->m_Cells->m_Down->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next
            && m.m_Cols->m_Next->m_Next->m_Idx == 5
            && m.m_Cols->m_Next->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Row == 1
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Col == 5
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Data == 30
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next->m_Next
            && m.m_Cols->m_Next->m_Next->m_Next->m_Idx == 190
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Row == 230
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Col == 190
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Data == 50
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Rows->m_Cells == m.m_Cols->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Cells == m.m_Cols->m_Cells);
    assert (m.m_Rows->m_Next->m_Cells->m_Right == m.m_Cols->m_Next->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Next->m_Cells == m.m_Cols->m_Next->m_Cells->m_Down);
    assert (m.m_Rows->m_Next->m_Next->m_Next->m_Cells == m.m_Cols->m_Next->m_Next->m_Next->m_Cells);
    assert (removeCell(&m, 0, 1));
    assert (!removeCell(&m, 0, 1));
    assert (!removeCell(&m, 1, 2));
    assert (m.m_Rows
            && m.m_Rows->m_Idx == 1
            && m.m_Rows->m_Cells
            && m.m_Rows->m_Cells->m_Row == 1
            && m.m_Rows->m_Cells->m_Col == 0
            && m.m_Rows->m_Cells->m_Data == 20
            && m.m_Rows->m_Cells->m_Right
            && m.m_Rows->m_Cells->m_Right->m_Row == 1
            && m.m_Rows->m_Cells->m_Right->m_Col == 5
            && m.m_Rows->m_Cells->m_Right->m_Data == 30
            && m.m_Rows->m_Cells->m_Right->m_Right == nullptr);
    assert (m.m_Rows->m_Next
            && m.m_Rows->m_Next->m_Idx == 2
            && m.m_Rows->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Cells->m_Row == 2
            && m.m_Rows->m_Next->m_Cells->m_Col == 1
            && m.m_Rows->m_Next->m_Cells->m_Data == 40
            && m.m_Rows->m_Next->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next
            && m.m_Rows->m_Next->m_Next->m_Idx == 230
            && m.m_Rows->m_Next->m_Next->m_Cells
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Row == 230
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Col == 190
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Data == 50
            && m.m_Rows->m_Next->m_Next->m_Cells->m_Right == nullptr);
    assert (m.m_Rows->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Cols
            && m.m_Cols->m_Idx == 0
            && m.m_Cols->m_Cells
            && m.m_Cols->m_Cells->m_Row == 1
            && m.m_Cols->m_Cells->m_Col == 0
            && m.m_Cols->m_Cells->m_Data == 20
            && m.m_Cols->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next
            && m.m_Cols->m_Next->m_Idx == 1
            && m.m_Cols->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Cells->m_Row == 2
            && m.m_Cols->m_Next->m_Cells->m_Col == 1
            && m.m_Cols->m_Next->m_Cells->m_Data == 40
            && m.m_Cols->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next
            && m.m_Cols->m_Next->m_Next->m_Idx == 5
            && m.m_Cols->m_Next->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Row == 1
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Col == 5
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Data == 30
            && m.m_Cols->m_Next->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next->m_Next
            && m.m_Cols->m_Next->m_Next->m_Next->m_Idx == 190
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Row == 230
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Col == 190
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Data == 50
            && m.m_Cols->m_Next->m_Next->m_Next->m_Cells->m_Down == nullptr);
    assert (m.m_Cols->m_Next->m_Next->m_Next->m_Next == nullptr);
    assert (m.m_Rows->m_Cells == m.m_Cols->m_Cells);
    assert (m.m_Rows->m_Cells->m_Right == m.m_Cols->m_Next->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Cells == m.m_Cols->m_Next->m_Cells);
    assert (m.m_Rows->m_Next->m_Next->m_Cells == m.m_Cols->m_Next->m_Next->m_Next->m_Cells);
    freeMatrix(&m);
    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
