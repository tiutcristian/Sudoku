#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

class Board {
    private:
        int val[9][9];
        int bitmask_line[9];
        int bitmask_col[9];
        int bitmask_square[9];
        int nr_zero;

    public:
        Board();
        void set(int l, int c, int v);
        int get(int l, int c) { return val[l][c]; }
        int get_posib(int l, int c) { return (1<<9) - 1 - (bitmask_line[l] | bitmask_col[c] | bitmask_square[l/3*3 + c/3]); }
        bool is_posib(int l, int c, int v) { return ((bitmask_line[l] | bitmask_col[c] | bitmask_square[l/3*3 + c/3]) & nr2bit(v)) == 0;  }
        inline int get_nr_posib(int l, int c);
        bool is_complete() { return nr_zero == 0; }
        static int nr2bit(int nr) { return 1 << (nr - 1); }
        static int bit2nr(int bit);
        void swap(Board &other);
        int get_nr_zero(){ return nr_zero; }
        bool no_complete_lcs();
};

#endif // BOARD_H_INCLUDED
