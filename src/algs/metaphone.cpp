/*  Metaphone Conversion Notes

  When I found this Algorithm, in article, there were discrepancies between
  the BASIC code and the verbal description. The discrepances look like they
  could have been caused by typing errors in the article.

  I have included the BASIC code from this article for the specific purpose
  of presenting the Algorithm the way it was originally described.
  I have tried to reproduce the BASIC EXACTLY the way it appeared. So when
  you see "ENAM" with nothing behind it, that is how it was presented.

  Lawrence Philips has no doubt spent a lot of time in the development of
  this algorithm. I am trusting that the algorithm described has been
  throughly tested to the best of his ability.

  It was my intention to reproduce it using his rules as best as I could
  discern them.

  It looks like it works better than Soundex. Thank You Lawrence.

  To anyone passing this along. Please include all of the notes they
  are part of the documentation and credits. Thanks

  Mike Kuhn (mkuhn@rhlab.com)

  Michael J. Kuhn        Computer Systems Consultant
                         5916 Glenoak Ave.
                         Baltimore, MD 21214-2009
                         410-254-7060

  P.S.
  A version of this routine in the Informix Archive was done by:

               Sadru Fidai   Munics Information Systems
                             50 Mount Prospect Ave
                             Clifton NJ 07013   (201)778-7753
               aol.com!SFidai

  Sadru called me to discuss this and said the following:

    His routine was NOT done from the article published in "Computer Language".
    He started with a working version from a PICK system that was using this.
    He had 2,000+ names with metaphone from the PICK system that he used
    to test the C code with.

    You might want to check this routine out.

    I did not use his routine at the time because there was no verbal
    explanation of the transformations. Also my intent was to be able
    to easily modify the transformation rules with some of my own.

    I did a mod 100 of my 20,726 test names and got 221 scattered names.
    I then computed Metaphone for Sadru version and mine. There were 14
    differences. Excluding the trailing S's in his, which I eliminated.
    I also changed his code so that O was a ZERO.  The differences account
    for changes I MADE and interpretation of transformation rules.

    At this point I have no need to do a more comprehensive analysis.

         lastname         Mike Kuhn  Sadru Fidai

         ANASTHA            ANS0       ANSX
         DAVIS-CARTER       TFSKRTR    TFXKRTR
         ESCARMANT          ESKRMNT    EXKRMNT
         MCCALL             MCL        MKKL
         MCCROREY           MCRR       MKKRR
         MERSEAL            MRSL       MRXL
         PIEURISSAINT       PRSNT      PRXNT
         ROTMAN             RTMN       RXMN
         SCHEVEL            SXFL       SKFL
         SCHROM             SXRM       SKRM
         SEAL               SL         XL
         SPARR              SPR        XPR
         STARLEPER          STRLPR     XTRLPR
         THRASH             TRX        0RX
*/
#include "metaphone.h"

#include <stdio.h>
#include <string.h>
#include <cctype>  // for isalpha
#include <string>
#include <iostream>

using namespace std;

#define TRUE  (1)
#define FALSE (0)
#define NULLCHAR (char *) 0

char VOWELS[]="AEIOU",
     FRONTV[]="EIY",   /* special cases for letters in FRONT of these */
     VARSON[]="CSPTG", /* variable sound--those modified by adding an "h"    */
     DOUBLE[]=".";     /* let these double letters through */

char excpPAIR[]="AGKPW", /* exceptions "ae-", "gn-", "kn-", "pn-", "wr-" */
     nextLTR[] ="ENNNR";
char *chrptr, *chrptr1;

string phonetic(string name) {

    int  ii, jj, silent, hard, Lng, lastChr;
    string metaph;
    unsigned int metalen = 20;
    char curLtr, prevLtr, nextLtr, nextLtr2, nextLtr3;

    int vowelAfter, vowelBefore, frontvAfter;

    char wname[60];
    char *ename=wname;

    // Make uppercase
    jj = 0;
    for (ii=0; name[ii] != '\0'; ii++) {
        if ( isalpha(name[ii]) ) {
            ename[jj] = toupper(name[ii]);
            jj++;
        }
    }
    ename[jj] = '\0';

    // Given string was empty
    if (strlen(ename) == 0) return metaph;

    /* if ae, gn, kn, pn, wr then drop the first letter */
    if ( (chrptr=strchr(excpPAIR,ename[0]) ) != NULLCHAR ) {
        chrptr1 = nextLTR + (chrptr-excpPAIR);
        if ( *chrptr1 == ename[1] )  strcpy(ename,&ename[1]);
    }
                                                /* change x to s */
    if  (ename[0] == 'X') ename[0] = 'S';
                                               /* get rid of the "h" in "wh" */
    if ( strncmp(ename,"WH",2) == 0 ) strcpy(&ename[1], &ename[2]);

    Lng = strlen(ename);
    lastChr = Lng -1;   /* index to last character in string makes code easier*/

                          /* Remove an S from the end of the string */
    if ( ename[lastChr] == 'S' ) {
        ename[lastChr] = '\0';
        Lng = strlen(ename);
        lastChr = Lng -1;
    }

    for (ii=0; ( (metaph.length() < metalen) && (ii < Lng) ); ii++) {

        curLtr = ename[ii];

        vowelBefore = FALSE;  prevLtr = ' ';
        if (ii > 0) {
            prevLtr = ename[ii-1];
            if ( strchr(VOWELS,prevLtr) != NULLCHAR ) vowelBefore = TRUE;
        }
                                          /* if first letter is a vowel KEEP it */
        if (ii == 0 && (strchr(VOWELS,curLtr) != NULLCHAR) ) {
            metaph += &curLtr;
            continue;
        }

        vowelAfter = FALSE;   frontvAfter = FALSE;   nextLtr = ' ';
        if ( ii < lastChr ) {
            nextLtr = ename[ii+1];
            if ( strchr(VOWELS,nextLtr) != NULLCHAR ) vowelAfter = TRUE;
            if ( strchr(FRONTV,nextLtr) != NULLCHAR ) frontvAfter = TRUE;
        }
                                     /* skip double letters except ones in list */
        if (curLtr == nextLtr && (strchr(DOUBLE,nextLtr) == NULLCHAR) ) continue;

        nextLtr2 = ' ';
        if (ii < (lastChr-1) ) nextLtr2 = ename[ii+2];

        nextLtr3 = ' ';
        if (ii < (lastChr-2) ) nextLtr3 = ename[ii+3];

        switch (curLtr) {

            case 'B':
                silent = FALSE;
                // For words like 'bo/mb/'
                if (ii == lastChr && prevLtr == 'M') silent = TRUE;
                if (! silent) metaph += &curLtr;
                break;


            case 'C':                   /*silent -sci-,-sce-,-scy-;  sci-, etc OK*/
                if (! (ii > 1 && prevLtr == 'S' && frontvAfter) ) {
                    // Like in 'con/sci/ence'
                    if ( ii > 0 && nextLtr == 'I' && nextLtr2 == 'A' ){
                        metaph += "X";
                    }
                    // Like in 'scien/ce/'
                    else if (frontvAfter) {
                        metaph +="S";
                    }
                    // Like in '/sch/ool'
                    else if (ii > 1 && prevLtr == 'S' && nextLtr == 'H') {
                        metaph +="K";
                    }
                    else if (nextLtr == 'H'){
                        // like in '/ch/aracter'
                        if (ii == 0 && (strchr(VOWELS,nextLtr2) == NULLCHAR) ) {
                            metaph +="K";
                        }
                        else {
                            // like in '/ch/ant'
                            metaph +="X";
                        }
                    }
                    // like in 'a/cc/ess'
                    else if (prevLtr == 'C') {
                        metaph +="C";
                    }
                    else {
                        metaph +="K";
                    }
                }
                break;

            case 'D':
                // like in 'bri/dg/e'
                if (nextLtr == 'G' && (strchr(FRONTV,nextLtr2) != NULLCHAR)) {
                    metaph +="J";
                }
                else {
                    metaph +="T";
                }
                break;

            case 'G':
                silent=FALSE;
                             /* SILENT -gh- except for -gh and no vowel after h */
                if ( (ii < (lastChr-1) && nextLtr == 'H')
                        && (strchr(VOWELS,nextLtr2) == NULLCHAR) ) {

                    silent=TRUE;
                }
                if ( (ii == (lastChr-3))
                       && nextLtr == 'N' && nextLtr2 == 'E' && nextLtr3 == 'D') {

                    silent=TRUE;
                }
                else if ( (ii == (lastChr-1)) && nextLtr == 'N') {
                    silent=TRUE;
                }

                if (prevLtr == 'D' && frontvAfter) silent=TRUE;

                // like in 'bra/gg/ing'
                if (prevLtr == 'G') {
                    hard=TRUE;
                }
                else {
                    hard=FALSE;
                }

                if (!silent) {
                    if (frontvAfter && (! hard)) {
                        metaph += "J";
                    }
                    else {
                        metaph += "K";
                    }
                }

                break;

            case 'H':
                silent = FALSE;
                if ( strchr(VARSON,prevLtr) != NULLCHAR ) silent = TRUE;

                if ( vowelBefore && !vowelAfter) silent = TRUE;

                if (!silent) metaph +=&curLtr;

                break;

    /*
        Cases F - N do nothing, keep them
    */
            case 'F':
            case 'J':
            case 'L':
            case 'M':
            case 'N':
            case 'R':
                metaph += &curLtr;
                break;

            case 'K':
                if (prevLtr != 'C') metaph += &curLtr;
                break;

            case 'P':
                // like in 'ele/ph/ant'
                if (nextLtr == 'H') {
                    metaph += "F";
                }
                else {
                    metaph += "P";
                }
                break;

            case 'Q':
                metaph += "K";
                break;

            case 'S':
                // as in 'mis/sio/n'
                if (ii > 1 && nextLtr == 'I'
                        && ( nextLtr2 == 'O' || nextLtr2 == 'A') ) {

                    metaph += "X";
                }
                // as in '/sh/oot'
                else if (nextLtr == 'H') {
                    metaph += "X";
                }
                else{
                    metaph += "S";
                }
                break;

            case 'T':
                // as in 'execu/tio/n''
                if (ii > 1 && nextLtr == 'I'
                        && ( nextLtr2 == 'O' || nextLtr2 == 'A') ) {
                    metaph += "X";
                }
                else if (nextLtr == 'H'){  /* The=0, Tho=T, Withrow=0 */
                    if (ii > 0 || (strchr(VOWELS,nextLtr2) != NULLCHAR) ){
                        metaph += "0";
                    }
                    else {
                        metaph +="T";
                    }
                }
                // for words like 'hi/tch/' omit the t, otherwise add the t
                else if (! (ii < (lastChr-2) && nextLtr == 'C' && nextLtr2 == 'H')) {
                    metaph += "T";
                }
                break;

            case 'V':
                metaph += "F";
                break;

            case 'W':
            case 'Y':
                if (ii < lastChr && vowelAfter) metaph +=&curLtr;
                break;

            case 'X':
                metaph += "KS";
                break;

            case 'Z':
                metaph += "S";
                break;
            }

    }

    /*  DON'T DO THIS NOW, REMOVING "S" IN BEGINNING HAS the same effect
        with plurals, in addition imbedded S's in the Metaphone are included
      Lng = strlen(metaph);
      lastChr = Lng -1;
      if ( metaph[lastChr] == 'S' && Lng >= 3 ) metaph[lastChr] = '\0';
    */

    return metaph;
}

string metaphone(string s) {
    string metaphone;
    s = phonetic(s);

    // Clean up the outputted metaphone string
    for (unsigned int i = 0; i < s.length(); i++) {
        if (isalnum(s[i])) {
            metaphone += s[i];
        }
    }

    return metaphone;
}
