# 1. definition of input and outputs

# input

1. user should enter the Number of variables, the number of minterms(including the number of don't care minterms), and then the number of don't care.
2. The number of minterms cannot be greater than 2^number of variables nor smaller than 1.
3. The number of Don't-Care minterms cannot be greater than the  number of all minterms nor smaller than 0.
4. then we scan the minterms indices in decimal format in an array.
5. user should enter the minterm indices as decimal numbers in ascending order (MintermIndicesDecimal[i]).
6. each minterm indices value entered should be smaller than 2^number of variables.
7. then we scan the DontCare minterms indices in decimal format in another array.
8. user should enter the minterm indices as decimal numbers in ascending order (DontCareDecimal[i]).
9. each DontCare minterm indices value entered should be smaller than 2^number of variables.

# output

1. we will get the optimized boolean expression of the given function.
2. the output expression will be minimized expression with characters like a, a,b,b',...

# 2. Functionality and scoping

Quine-McCluskey (QM) method is one of the most powerful techniques to simplify Boolean expressions
so, we will minimize the boolean expression using the concept of Quine-McCluskey Method in c language.

The QM method is based on the reduction principle, which says that (AB+AB` = A).
 It means that when two terms containing the same variables differ only in one variable, they can be
combined together and form a new term smaller by one literal. 

All the terms in the Boolean function are tested for possible combinations of any two of them, after which
a new set of terms that are smaller by one literal are produced and are further tested
under the same procedures for further reduction. The same procedures will be repeated until no terms can be combined anymore. 

# 3. Procedures and implementation of the QM method 

1. All the minterms and don't care terms entered by the user are converted from decimal to binary numbers.
2. then they are arranged into different groups according to the number of 1s in the binary representation.  These groups are put in ascending order in a Column.
3. we will store these binary numbers in the two-dimensional array
4. Every two minterms from two adjacent groups are paired for possible combinations if they only differ in one variable.
5. The digit which is different is replaced by ‘X’(which is denoted by 2). After the first round of pairing, a new set of terms that are smaller by one literal are produced and placed in a column. Terms in the Column are further paired for further reduction. The same procedures will be
6. repeated until no terms can be paired anymore.
7. To store the terms in the columns, the four-dimensional array Column[][][][] is used.
8. terms with more than one ‘X’ will always have duplicates. Thus, all the duplicates need to be removed. The remaining irreducible terms are PIs.
9. A ‘PI chart’ will be made. Each column represents a minterm and each row represents a PI. In the first step, all the Don’t-Care minterms are removed.
10. Column with only a single element column indicates a minterm covered by only one PI, which means this PI is EPI. All the rows of EPI and the corresponding columns that are covered will be removed.
11. The remaining PIs and minterms will form a new Reduced PI chart. The next step is to find a set of PIs that cover all the terms in the Reduced PI chart but contain the least possible number of PIs. This set of PIs will be the rest EPIs.


