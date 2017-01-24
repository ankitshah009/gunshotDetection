/* ========================================================================
    JanusRTk   Janus Recognition Toolkit
               ------------------------------------------------------------
               Object: Language Model --  n > 3 possible
               ------------------------------------------------------------

    Author  :  Florian Metze
    Module  :  ngramLM.c
    Date    :  $Id: ngramLM.c 3420 2011-03-24 00:47:31Z metze $

    Remarks :  Generic Language Model for the New Janus Decoder
               Tightly integrated with the Language Model LookAhead
               Derived from LModelLong

   ========================================================================

    This software was developed by

    the  University of Karlsruhe       and  Carnegie Mellon University
         Dept. of Informatics               Dept. of Computer Science
         ILKD, Lehrstuhl Prof.Waibel        Alex Waibel's NN & Speech Group
         Am Fasanengarten 5                 5000 Forbes Ave
         D-76131 Karlsruhe                  Pittsburgh, PA 15213
         - West Germany -                   - USA -

    This software is part of the JANUS Speech- to Speech Translation Project

    USAGE PERMITTED ONLY FOR MEMBERS OF THE JANUS PROJECT
    AT CARNEGIE MELLON UNIVERSITY OR AT UNIVERSITAET KARLSRUHE
    AND FOR THIRD PARTIES ONLY UNDER SEPARATE WRITTEN PERMISSION
    BY THE JANUS PROJECT

    It may be copied  only  to members of the JANUS project
    in accordance with the explicit permission to do so
    and  with the  inclusion  of  the  copyright  notices.

    This software  or  any  other duplicates thereof may
    not be copied or otherwise made available to any other person.

    No title to and ownership of the software is hereby transferred.

   ========================================================================

    $Log$
    Revision 4.7  2004/10/29 09:34:07  metze
    Fixed problems with 'typedef UINT LVX'

    Revision 4.6  2004/10/28 16:29:18  fuegen
    added some error messages

    Revision 4.5  2004/09/24 08:13:27  fuegen
    windows code cleaning

    Revision 4.4  2004/09/22 16:26:35  fuegen
    Mapping of log(0) representation used by the SRILM-Toolkit (== -99)
    to a usable value. Can be configured with -log0 and -log0Val.

    Revision 4.3  2004/09/16 09:08:25  fuegen
    Added functionality for reading LMs with unsorted n-gram section,
    e.g. produced by the SRILM-Toolkit.

    Revision 4.2  2003/11/06 17:45:47  metze
    CLeaned up vocab mapping

    Revision 4.1  2003/08/14 11:20:04  fuegen
    Merged changes on branch jtk-01-01-15-fms (jaguar -> ibis-013)

    Revision 1.1.2.23  2003/07/15 16:48:29  fuegen
    added forward declaration of putsItf function

    Revision 1.1.2.22  2003/07/15 16:37:51  fuegen
    changed LingKS load/save interface
    added lingKSPutsFct

    Revision 1.1.2.21  2003/06/06 08:05:59  fuegen
    made gcc 3.3 clean

    Revision 1.1.2.20  2003/05/08 16:41:54  soltau
    Purified!

    Revision 1.1.2.19  2003/01/29 16:00:43  metze
    Bugfix for linkA when reading dumps

    Revision 1.1.2.18  2003/01/21 10:51:09  metze
    Fix for empty line at start

    Revision 1.1.2.17  2002/11/21 17:10:10  fuegen
    windows code cleaning

    Revision 1.1.2.16  2002/11/21 14:10:10  metze
    Beautified error messages

    Revision 1.1.2.15  2002/11/20 10:04:41  metze
    Typo fixed

    Revision 1.1.2.14  2002/11/20 10:00:24  metze
    Replaced '\n' in matches

    Revision 1.1.2.13  2002/11/19 11:26:00  soltau
    NGramLMReadArpabo : reduced verbosity

    Revision 1.1.2.12  2002/11/15 13:05:52  metze
    Removed superfluous output

    Revision 1.1.2.11  2002/10/04 09:40:35  metze
    Avoid segfault by extra check

    Revision 1.1.2.10  2002/08/30 14:20:15  metze
    define SOLARIS -> SUN

    Revision 1.1.2.9  2002/08/01 13:42:31  metze
    Fixes for clean documentation.

    Revision 1.1.2.8  2002/07/02 12:20:39  metze
    Loading of LMs works for fancy headers, too

    Revision 1.1.2.7  2002/06/13 08:07:40  metze
    Added dirty as a function in LMs

    Revision 1.1.2.6  2002/06/12 10:10:10  metze
    Fixed WARNINGS

    Revision 1.1.2.5  2002/06/12 09:44:16  metze
    Checks for valid LCT

    Revision 1.1.2.4  2002/05/03 14:01:23  metze
    Freeing of LingKS now works properly

    Revision 1.1.2.3  2002/05/02 12:01:17  soltau
    Removed unnecessary includes

    Revision 1.1.2.2  2002/04/29 13:32:50  metze
    Beautification

    Revision 1.1.2.1  2002/04/29 12:05:12  metze
    Renaming of LModelNJD to NGramLM

    Revision 1.1.2.38  2002/03/13 16:06:56  metze
    Distance LMs (with hashed LCTs)

    Revision 1.1.2.37  2002/03/07 10:17:21  metze
    Added LCT handling with hashtable for LModelNJD

    Revision 1.1.2.36  2002/02/15 16:24:33  metze
    Fixes for compilation under SUN

    Revision 1.1.2.35  2002/02/07 12:11:50  metze
    Changes in interface to LM score functions

    Revision 1.1.2.34  2002/01/19 11:36:24  metze
    Added function to return the substitutions section at Tcl-level

    Revision 1.1.2.33  2002/01/16 11:04:39  soltau
    CreateLCT: fixed bitmask settings for long lct's

    Revision 1.1.2.32  2002/01/14 10:30:28  metze
    Cleaned up reading/ writing of dumps

    Revision 1.1.2.31  2001/10/25 16:27:09  soltau
    beautified

    Revision 1.1.2.30  2001/10/22 08:40:26  metze
    Changed interface to score functions

    Revision 1.1.2.29  2001/10/03 15:54:32  metze
    Correct setting of freeLCT

    Revision 1.1.2.28  2001/10/02 18:57:41  metze
    Made info for vocab mapper more correct

    Revision 1.1.2.27  2001/09/26 14:39:05  metze
    Made read method work for both ARPABO and dump files

    Revision 1.1.2.26  2001/09/20 11:32:03  metze
    Implemented scoring of full utterances

    Revision 1.1.2.25  2001/07/18 15:42:39  metze
    Made quantization a run-time option

    Revision 1.1.2.24  2001/07/11 15:09:13  metze
    Added dump routines
    Bug fix in ScoreFct: ScoreFct, ScoreArrayFct and old LMs have identical results for 3G
    Added Compression to bytes for all MGrams

    Revision 1.1.2.23  2001/06/28 11:43:41  metze
    Hopefully fixed the last bug concerning Linux/ SunOS and the LCTs

    Revision 1.1.2.22  2001/06/21 18:47:53  metze
    Hack Alert: calculation des 'lct' tres moche, mais ca roule (on veut le croire)
    It's not quite clear why the routines we had before didn't always work, but
    maybe we'll find out (one day ...)

    Revision 1.1.2.21  2001/06/13 09:43:49  metze
    Made LCT handling work on SUNs

    Revision 1.1.2.20  2001/06/01 10:07:11  metze
    Made changes necessary for decoding along lattices

    Revision 1.1.2.19  2001/05/23 08:10:46  metze
    PartFill included, cleaned up code

    Revision 1.1.2.18  2001/05/11 16:39:31  metze
    Cleaned up LCT interface

    Revision 1.1.2.17  2001/05/09 14:57:46  metze
    Two choices for LCT handling

    Revision 1.1.2.16  2001/05/03 07:17:37  metze
    Made compressed LM work for bigrams

    Revision 1.1.2.15  2001/04/27 07:38:35  metze
    General access functions to LM via 'LCT' implemented

    Revision 1.1.2.14  2001/04/24 10:21:35  metze
    Last stable version that uses old LM-Interface

    Revision 1.1.2.13  2001/03/23 14:41:14  metze
    Fixed bug that crept in during merging

    Revision 1.1.2.12  2001/03/23 13:41:44  metze
    Compressed link arrays (two-level addressing)

    Revision 1.1.2.11  2001/03/21 12:26:25  metze
    Added option to quantize highest-order probabilities

    Revision 1.1.2.10  2001/03/20 17:07:06  soltau
    Added define to switch between old backoff and correct backoff unigram incorporation

    Revision 1.1.2.9  2001/03/16 12:15:19  metze
    Bugfix for SearchMGrams

    Revision 1.1.2.8  2001/03/15 18:30:49  metze
    Bugfix for ScoreArray

    Revision 1.1.2.7  2001/03/15 15:42:58  metze
    Re-implementation of LM-Lookahead

    Revision 1.1.2.6  2001/03/12 17:55:50  metze
    Made ScoreArray faster

    Revision 1.1.2.5  2001/03/06 18:07:03  metze
    LModelNJDScoreArray and LModelNJDScore now do the same thing

    Revision 1.1.2.4  2001/03/05 08:39:39  metze
    Cleaned up treatment of exact LM in LMLA

    Revision 1.1.2.3  2001/02/28 17:52:41  metze
    Removed pragmas to avoid confusion of the SUN-compiler

    Revision 1.1.2.2  2001/02/27 15:10:28  metze
    LModelNJD and LMLA work with floats


   ======================================================================== */


#include <ctype.h>
#include <sys/mman.h>

#include "mach_ind_io.h"
#include "ngramLM.h"
#include "lks.h"

char ngramLMRCSVersion[]= 
     "@(#)1$Id: ngramLM.c 3420 2011-03-24 00:47:31Z metze $";


int sri_cache_hit   = 0;
int sri_cache_miss  = 0;
int lcta_cache_hit  = 0;
int lcta_cache_miss = 0;

/* ------------------------------------------------------------------------
    Forward Declarations
   ------------------------------------------------------------------------ */

#define BITSHIFT  8*sizeof(LVX)

extern  TypeInfo  NGramLMInfo;

static  int       NGramLMInitialized = 0;
static  NGramLM   NGramLMDefault;
static  LVX       lvxBuffer[1024];

/* stuff for lmP->ngspCL */
static Tcl_DString    *SRIdstrPtr;
static Tcl_Obj        *SRIstrObjPtr;
static NGramScorePair currNGSP;

/* stuff for lmP->lctapCL */
static NGramLCTAPair currLCTAP;

typedef enum { 
  LM_LINE, 
  LM_DATA, 
  LM_1GRAMS, 
  LM_2GRAMS, 
  LM_3GRAMS, 
  LM_NGRAMS, 
  LM_UNIGRAMS, 
  LM_SUBS, 
  LM_END 
} ArpaboLModelSection;

static int      NGramLMIndex          (NGramLM* NGramLM,  char* name) ;
static int      NGramLMFindMGram      (NGramLM* lmP, int m, LVX *arr, int *searchX);
static int      NGramLMInitMGram      (NGramLM* lmP, int m, int itemN);
static int      NGramLMDeInitMGram    (NGramLM* lmP, int m);

static int      NGramLMReadArpabo     (NGramLM* lmP, FILE* fp, char *txt, int quant);
static int      NGramLMSaveItf        (ClientData cd, int argc, char *argv[]);
static int      NGramLMLoadItf        (ClientData cd, int argc, char *argv[]);
static int      NGramLMPutsItf        (ClientData cd, int argc, char *argv[]);

static lmScore  NGramLMScore                 (LingKS* lksP, LCT lct, LVX w,        int usehistory);
static int      NGramLMScoreArray            (LingKS* lksP, LCT lct, lmScore *arr, int usehistory);
static lmScore  NGramLMScoreSriLMServer      (LingKS* lksP, LCT lct, LVX w,        int usehistory);
static int      NGramLMScoreArraySriLMServer (LingKS* lksP, LCT lct, lmScore *arr, int usehistory);
static int      NGramLMListReInit            (NGramLM* lmP);
static int      NGramLMHashStatus            (NGramLM* lmP);

/* ========================================================================
    LCT handling
   --------------
    We could have different functions for different N-Grams to speed up
    the calculations, it would be possible to use LCT as an HashKey if
    using LVX > 16bit or n > 3 (and not use LCT = 8byte)

    CAVEAT: don't expect that expand(reduce(extend(i)))=i, you won't be
      able to extend an LCT once you reduced it!
   ======================================================================== */


/* Reduce an lct by n words, you can then get the first
   or second word */
static LCT reduceLCT (LingKS* lksP, LCT lct, int n)
{
  return lct & (lksP->data.ngramLM->bitmask >> (n*BITSHIFT));
}


/* Extend an lct by a word */
static LCT extendLCT (LingKS* lksP, LCT lct, LVX lvx)
{
  return ((lct << BITSHIFT) + (LCT) lvx) & lksP->data.ngramLM->bitmask;
}


/* Call this to free an lct and all its dependent lcts
   (used for grammars and so on) */
static int freeLCT (LingKS* lksP, LCT lct)
{
  return TCL_OK;
}

#ifdef SUN

/* ------------------------------------------------------------------------
    solaris dependent routines
   ------------------------------------------------------------------------ */

/* decodeLCT returns the last n words represented by lct.
   If 'n==-1' the default history will be used.
   A trigram LM (n==3) will have history==2 */
static int decodeLCT (LingKS* lksP, LCT lct, LVX* lvxA, int n)
{
  int i, o;
  LVX  *v = (LVX*) &lct;
  lvxA[0] = LVX_NIL;

  if (n < 0 || n >= lksP->data.ngramLM->order)
    n = lksP->data.ngramLM->history;
  o = sizeof(LCT)/sizeof(LVX)-n;

  for (i = 0; i < n; i++) {
    lvxA[i] = v[i+o];
    assert (lvxA[i] < lksP->data.ngramLM->list.itemN);
  }

  return n;
}

/* createLCT initializes an lct, you should use lvX==<s> */
static LCT createLCT (LingKS* lksP, LVX lvX)
{
  NGramLM* lmP = lksP->data.ngramLM;
  LCT          N = 0;
  int          i;
  LCT        lct;

  /* For simplicity, distance LMs are only supported with hashed LCTs */
  if (lmP->history >= lmP->order) {
    INFO ("Assuming distance-%d %d-gram, switching to hashed LCTs.\n",
	  lmP->history-lmP->order+1, lmP->order);
    lmP->hash = 1;
    NGramLMHashStatus (lmP);
    return lksP->createLCT (lksP, lvX);
  }

  N              = ~N;
  if (sizeof(LCT) == lmP->history*sizeof(LVX)) {
    lmP->bitmask   = N;
  } else { 
    lmP->bitmask   = (N >> ((sizeof(LCT)/sizeof(LVX)-lmP->history)*BITSHIFT));
  }
  lct =  ((LCT) lvX) & lmP->bitmask;
  for (i = 0; i < lmP->history; i++)
    lct = lksP->extendLCT (lksP, lct, lvX);

  return lct;
}

#else

/* ------------------------------------------------------------------------
    non-solaris dependent routines
   ------------------------------------------------------------------------ */

static int decodeLCT (LingKS* lksP, LCT lct, LVX* lvxA, int n)
{
  int i, j;
  LVX  *v = (LVX*)((void*)&lct);
  lvxA[0] = LVX_NIL;

  if (n < 0 || n >= lksP->data.ngramLM->order)
    n = lksP->data.ngramLM->history;

  for (i = 0, j = n-1; i < n; i++) {
    lvxA[i] = v[j-i];
    assert (lvxA[i] < lksP->data.ngramLM->list.itemN);
  }

  return n;
}

static LCT createLCT (LingKS* lksP, LVX lvX)
{
  NGramLM*   lmP = lksP->data.ngramLM;
  LCT          N = 0;
  int          i;
  LCT        lct;

  /* For simplicity, distance LMs are only supported with hashed LCTs */
  if (lmP->history >= lmP->order) {
    INFO ("Assuming distance-%d %d-gram, switching to hashed LCTs.\n",
	  lmP->history-lmP->order+1, lmP->order);
    lmP->hash = 1;
    NGramLMHashStatus (lmP);
    return lksP->createLCT (lksP, lvX);
  }

  N              = ~N;
  if (sizeof(LCT) == lmP->history*sizeof(LVX)) {
    lmP->bitmask   = N;
  } else { 
    lmP->bitmask   = ~(N << (lmP->history*BITSHIFT));
  }
  lct =  ((LCT) lvX) & lmP->bitmask;
  for (i = 0; i < lmP->history; i++)
    lct = lksP->extendLCT (lksP, lct, lvX);

  return lct;
}

#endif

/* ========================================================================
    LCT handling by hash table
   ======================================================================== */

static int njdHashInit (NJDLCT* ptr, NJDLCT* key)
{
  (*ptr) = (*key);
  return TCL_OK;
}

static int njdHashCmp  (NJDLCT* ptr, NJDLCT* key)
{
  if (ptr->lvxN != key->lvxN)
    return 0;
  else {
    int i;
    for (i = 0; i < ptr->lvxN && ptr->lvxA[i] == key->lvxA[i]; i++);
    return (i == ptr->lvxN);
  }
}

#define njdlctMask 0xFFFF
static long njdHashKey (const NJDLCT *key)
{
/* Buggy njdHashKey replaced with Rogers Version
  unsigned long ret = (key->lvxN) ? key->lvxA[key->lvxN-1] & njdlctMask : 0;
*/
  unsigned long ret=0;
  int i;

  for(i=0;i<key->lvxN;i++){
    ret = 2087*ret + (unsigned long)key->lvxA[i];
  }
 return ret;
}

static LCT createLCT_hash (LingKS* lksP, LVX lvX)
{
  NGramLM*  lmP = lksP->data.ngramLM;
  NJDLCT      key;
  int           i;

  /* Clear the memory */
  listClear ((List*) &lmP->lctList);
  bmemClear (lmP->lctMem);

  /* You'll need a bigger tmplvxA then ... */
  assert (lmP->history < 256);

  /* Create the LCTs : generate hashkey */
  key.lvxN = lmP->history;
  key.lvxA = (LVX*) bmemAlloc (lmP->lctMem, lmP->history*sizeof (LVX));
  for (i = 0; i < key.lvxN; i++)
    key.lvxA[i] = lvX;

  return (LCT) listIndex ((List*) &lmP->lctList, (void*) &key, 1);
}

static LVX tmplvxA[256];

static LCT extendLCT_hash (LingKS* lksP, LCT lct, LVX lvX)
{
  NGramLM*   lmP = lksP->data.ngramLM;
  NJDLCT*    ptr = lmP->lctList.itemA + (int) lct;
  NJDLCT     key;
  int        idx;

  /* Check for valid lct */
  assert ((int) lct >= 0);
  assert ((int) lct <  lmP->lctList.itemN);

  /* Extend the LCTs : generate hashkey */
  key.lvxN = ptr->lvxN;
  key.lvxA = tmplvxA;
  memcpy (key.lvxA, ptr->lvxA+1, (key.lvxN-1)*sizeof(LVX));
  key.lvxA[key.lvxN-1] = lvX;
  
  /* Hash */
  idx = listIndex ((List*) &lmP->lctList, (void*) &key, 1);
  ptr = lmP->lctList.itemA + idx;

  /* Copy lvxA, if we generated a new key */
  if (ptr->lvxA == tmplvxA) {
    ptr->lvxA = (LVX*) bmemAlloc (lmP->lctMem, ptr->lvxN*sizeof(LVX));
    memcpy (ptr->lvxA, tmplvxA, ptr->lvxN*sizeof(LVX));
  }

  return (LCT) idx;
}

static LCT reduceLCT_hash (LingKS* lksP, LCT lct, int n)
{
  NGramLM* lmP = lksP->data.ngramLM;
  NJDLCT*    ptr = lmP->lctList.itemA + (int) lct;
  NJDLCT     key;
  int        idx;

  /* Reduce the LCTs : generate hashkey */
  key.lvxN = ptr->lvxN-1;
  key.lvxA = tmplvxA;
  memcpy (key.lvxA, ptr->lvxA, key.lvxN*sizeof(LVX));

  /* Hash */
  idx = listIndex ((List*) &lmP->lctList, (void*) &key, 1);
  ptr = lmP->lctList.itemA + idx;

  /* Copy lvxA, if we generated a new key */
  if (ptr->lvxA == tmplvxA) {
    ptr->lvxA = (LVX*) bmemAlloc (lmP->lctMem, ptr->lvxN*sizeof(LVX));
    memcpy (ptr->lvxA, tmplvxA, ptr->lvxN*sizeof(LVX));
  }

  return (LCT) idx;
}

static int decodeLCT_hash (LingKS* lksP, LCT lct, LVX* lvxA, int n)
{
  NGramLM* lmP = lksP->data.ngramLM;
  NJDLCT* ptr;

  /* Check for valid lct */
  assert ((int) lct >= 0 && (int) lct < lmP->lctList.itemN);

  ptr = lmP->lctList.itemA + (int) lct;
  n = (ptr->lvxN < n) ? ptr->lvxN : n;
  memcpy (lvxA, ptr->lvxA, n*sizeof(LVX));
  return n;
}

static int freeLCT_hash (LingKS* lksP, LCT lct)
{
  return TCL_OK;
}

extern int NGramLMHashStatus (NGramLM* lmP)
{
  LingKS* lksP = lmP->lksP;
  if (lmP->hash) { /* Use hashed LCTs */
    lksP->createLCT      = createLCT_hash;
    lksP->reduceLCT      = reduceLCT_hash;
    lksP->extendLCT      = extendLCT_hash;
    lksP->decodeLCT      = decodeLCT_hash;
    lksP->freeLCT        = freeLCT_hash; 
  } else {         /* Don't use hashed LCTs */
    lksP->createLCT      = createLCT;
    lksP->reduceLCT      = reduceLCT;
    lksP->extendLCT      = extendLCT;
    lksP->decodeLCT      = decodeLCT;
    lksP->freeLCT        = freeLCT;
  }
  return TCL_OK;
}


/* ========================================================================
    File Loading
   --------------
    Loading of files and so on
   ======================================================================== */

typedef enum { ID_ARPABO, ID_DUMP, ID_MMAPI } idEnum;

static int idFile (FILE* fP, char *line)
{
  int i;
  short *s = (short*) line;

  for (i = 0; i < MAXLMLINE; i++) line[i] = 0;

  if (fread (s, sizeof (short), 1, fP) < 1) {
    WARN ("File very short ...\n");
  } else if (*s == 15 || *s == 3840) {
    if (fread (line+2, sizeof (char), 16, fP) == 16) {
      if (streq (line+2, "LMODELNJD-BEGIN"))
	return ID_DUMP;
      if (streq (line+2, "LMODELNJD-MMAPI"))
	return ID_MMAPI;
    }
  }

  if (line[0] == '\n') {
    line[0] = line[1];
    line[1] = 0;
  }
  if (line[1] != '\n')
    fgets (line + strlen (line), MAXLMLINE-1-strlen (line), fP);

  return ID_ARPABO;
}


/* ========================================================================
    NGramLMInitMGram
   --------------------
    Helper routines to (de-)initialize the structure for an M-Gram
   ======================================================================== */

static int NGramLMInitMGram (NGramLM* lmP, int m, int n)
{
  MGram* mg = lmP->mgram+m;

  mg->itemN     = n;
  mg->cprobA    = NULL;
  mg->probA     = NULL;
  mg->idA       = NULL;
  mg->cbackoffA = NULL;
  mg->backoffA  = NULL;
  mg->linkA     = NULL;
  mg->segTbl    = NULL;

  if ((mg->probA    = (lmScore*)        malloc ( n                     *sizeof(lmScore)))        == NULL)
    return TCL_ERROR;

  if (m > 0          &&
      (mg->idA      = (LVX*)            malloc ((n+1)                  *sizeof(LVX)))            == NULL)
    return TCL_ERROR;

  if (m < lmP->order - 1 && 
      (mg->backoffA = (lmScore*)        malloc ( n                     *sizeof(lmScore)))        == NULL)
    return TCL_ERROR;

  if (m < lmP->order - 1 &&
      (mg->linkA    = (LVX*)            malloc ((n+1)                  *sizeof(LVX)))            == NULL)
    return TCL_ERROR;

  if (m < lmP->order - 1 && 
      (mg->segTbl   = (unsigned int*)   malloc ((((n+1)>>(lmP->segSize))+1)*sizeof(int)))        == NULL)
    return TCL_ERROR;

  return TCL_OK;
}


int NGramLMDeInitMGram (NGramLM* lmP, int m)
{
  MGram* mg = lmP->mgram+m;
  if (mg->cprobA)    free (mg->cprobA);
  if (mg->probA)     free (mg->probA);
  if (mg->idA)       free (mg->idA);
  if (mg->cbackoffA) free (mg->cbackoffA);
  if (mg->backoffA)  free (mg->backoffA);
  if (mg->linkA)     free (mg->linkA);
  if (mg->segTbl)    free (mg->segTbl);
  mg->cprobA    = NULL;
  mg->probA     = NULL;
  mg->idA       = NULL;
  mg->cbackoffA = NULL;
  mg->backoffA  = NULL;
  mg->linkA     = NULL;
  mg->segTbl    = NULL;
  mg->itemN     = 0;  
  return TCL_OK;
}


/* ========================================================================
    NGramLMcompressMGrams
   -------------------------
    Compresses a set of M-Grams into an 8bit lookup-table
   ======================================================================== */

static int compressProbs (NGramLM* lmP, int m)
{
  MGram*     mgram = lmP->mgram + m;
  lmScore     *arr = mgram->probA;
  lmScore min, max;
  int            i;
  float          f;

  mgram->cprobA = (unsigned char*) calloc (mgram->itemN, sizeof (unsigned char));
  mgram->probA  = (lmScore*)       calloc (256,          sizeof (lmScore));
  min = max = arr[0];

  /* Find minimum and maximum value, calculate scaling factor */
  for (i = 0; i < mgram->itemN; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
  f = 256.0 / (max - min + 1);
  /* INFO ("Quantizing %d-gram scores, grain=%.2f.\n", m+1, 1/f); */

  /* Fill in the lookup indices */
  for (i = 0; i < mgram->itemN; i++)
    mgram->cprobA[i] = f * (arr[i] - min);

  /* Fill in the lookup table, do rounding (+ 2/f)*/
  for (i = 0; i < 256; i++)
    mgram->probA[i]  = min + (int)(.5/f) + i * (max - min + 1) / 256;

  /* Free the original table */
  free (arr);

  return TCL_OK;
}

static int compressBackoffs (NGramLM* lmP, int m)
{
  MGram*     mgram = lmP->mgram + m;
  lmScore     *arr = mgram->backoffA;
  lmScore min, max;
  int            i;
  float          f;

  if (!mgram->backoffA) return TCL_OK;

  mgram->cbackoffA = (unsigned char*) calloc (mgram->itemN, sizeof (unsigned char));
  mgram->backoffA  = (lmScore*)       calloc (256,          sizeof (lmScore));
  min = max = arr[0];

  /* Find minimum and maximum value, calculate scaling factor */
  for (i = 0; i < mgram->itemN; i++) {
    if (arr[i] < min) min = arr[i];
    if (arr[i] > max) max = arr[i];
  }
  f = 256.0 / (max - min + 1);
  INFO ("Quantizing %d-gram backoffs, grain=%.1f.\n", m+1, 1/f);

  /* Fill in the lookup indices */
  for (i = 0; i < mgram->itemN; i++)
    mgram->cbackoffA[i] = f * (arr[i] - min);

  /* Fill in the lookup table, do rounding (+ 2/f)*/
  for (i = 0; i < 256; i++)
    mgram->backoffA[i]  = min + (int)(.5/f) + i * (max - min + 1) / 256;

  /* Free the original table */
  free (arr);

  return TCL_OK;
}


/* ========================================================================
    ArpaboLMReadLine
   ------------------
    Reads a line from an Arpabo format LM file and interprets its value
   ======================================================================== */

static int NGramLMReadLine_N=0;

ArpaboLModelSection ArpaboLMReadLine (NGramLM* lmP, FILE* fP, char* line)
{
  NGramLMReadLine_N = 0;

  if (fP && (!fgets (line, MAXLMLINE-1, fP) || feof (fP)))         return LM_END;

  if (!strncmp    (line, "\\data\\", 6))                           return LM_DATA;
  if (!strncmp    (line, "\\unigrams:", 10))                       return LM_UNIGRAMS;
  if (!strncmp    (line, "\\subsmodel:", 11))                      return LM_SUBS;

  if (sscanf      (line, "\\%d-grams:", &NGramLMReadLine_N ) > 0)  return LM_NGRAMS;

  if (!strncmp    (line, "\\end\\", 5)) {
    /* Special case: some LMs continue with a subsmodel,
       so we detect the end-of-file... */
    return ArpaboLMReadLine (lmP, fP, line);
  }

  if (!strncmp (line, "\\", 1)) INFO("Unknown segment '%s'.\n", line);

  return LM_LINE;
}


/* ========================================================================
    NGramLMReadArpaboMGramCounts
   --------------------------------
    Finds the number of 1..N-Grams in the LM file and builds the
    M-Grams table
   ======================================================================== */

int NGramLMReadArpaboMGramCounts (NGramLM* lmP, FILE* fP, ArpaboLModelSection* id)
{
  ArpaboLModelSection lms = LM_END;
  char             line[MAXLMLINE];
  int		   ngramN[1000];
  int              i;

  lmP->order = 0;
  while ((lms = ArpaboLMReadLine (lmP, fP, line)) == LM_LINE) {
    int ngram, count;

    if (sscanf (line, "ngram %d=%d", &ngram, &count) != 2) {
      if (line[0] != '\n' && line[0] != '\r')
	INFO ("Format error; \\data\\ line ignored: '%s'", line);
      continue;
    }
    ngramN[lmP->order] = count;

    if (++lmP->order != ngram) {
      ERROR("\\Data section not ordered: order=%d, ngram=%d\n", lmP->order, ngram);
      return TCL_ERROR;
    }
  }
  lmP->mgram = (MGram*) calloc (lmP->order, sizeof (MGram));

  if (ngramN[0] > LVX_MAX) {
    ERROR ("NGramLMInitMGram: %d > LVX_MAX => edit slimits.h, recompile.\n", ngramN[0]);
    return TCL_ERROR;
  }

  for (i = 0; i < lmP->order; i++) {
    if (NGramLMInitMGram (lmP, i, ngramN[i]) != TCL_OK) {
      ERROR ("NGramLMInitMGram: Due to lack of memory your\n");
      ERROR ("language model could not be loaded. We apologize for\n");
      ERROR ("any inconvenience this may cause to your computing.\n");
      while (i >= 0)
	NGramLMDeInitMGram (lmP, i--);
      if (lmP->mgram) { free (lmP->mgram); lmP->mgram = NULL; }
      return TCL_ERROR;
    }
  }

  lmP->history = lmP->order - 1;
  if (id) *id = lms; 
  return TCL_OK;
}


/* ========================================================================
    NGramLMReadArpaboMGrams
   ---------------------------
    Reads the M-Gram section of an Arpabo-File into an NJD-LM object
   ======================================================================== */
static int unsortedLM   = 0;
static int unsortedLM_M = 0;
static int upsampledLM  = 0;
static int compressedLM = 0;

static int scanArpaboLine (char *text, char **ptr)
{
  int  i        = 0;
  char *scanner = text;

  while (*scanner != '\0') {
    /* Delete spaces */
    while (isspace(*scanner)) *scanner++ = '\0';
    if (*scanner != '\0') {
      /* Found a string */
      ptr[i++] = scanner;
      while (!isspace(*scanner)) scanner++;
    }
  }

  return i;
}


static int NGramLMReadArpaboMGrams (NGramLM* lmP, FILE* fP, int M, ArpaboLModelSection* id)
{
  ArpaboLModelSection lms;
  char          line[MAXLMLINE];
  char         *fieldP[1024];
  LVX           lvX[16];

  int           i, j, k, fields, fieldN;
  int           idx   = 0;
  int           lastj = -1;
  float         p;

  /* How many fields should one line have? */
  fieldN = (M == lmP->order) ? M+1 : M+2;

  /* Main loop */
  while (((lms = ArpaboLMReadLine (lmP, fP, line)) == LM_LINE) &&
         (idx < lmP->mgram[M-1].itemN)) {

    fields = scanArpaboLine (line, fieldP);
    if (fields != fieldN && fields != fieldN-1) {
      ERROR ("%d-gram table: line starting with '%s' invalid, skipping.\n", M, line);
      continue;
    }

    if (M == 1) { /* ---- UNIGRAM part */

      if (NGramLMIndex (lmP, fieldP[1]) >= 0) {
        ERROR("Word '%s' already exists in '%s', ignoring.\n", fieldP[1], lmP->lksP->name);
        lmP->mgram[M-1].itemN--;
        continue;
      }
      if (idx != (i = listNewItem((List*)&(lmP->list), (ClientData)fieldP[1]))) {
        ERROR("Word '%s' got wrong index %d (not %d).\n", fieldP[1], i, idx);
        continue;
      }
      lmP->list.itemA[idx].lmP = lmP;

    } else { /* ---- 2, 3, ... N-gram part */

      lvX[0] = 0;
      for (i = 1; i <= M; i++) {
        if ((j = NGramLMIndex (lmP, fieldP[i])) < 0) {
          ERROR ("%d-gram table: word '%s' not found, ignoring line.\n", M, fieldP[i]);
          lvX[0] = LVX_NIL;
        } else {
          lvX[i] = (LVX) j;
        }
      }
      if (lvX[0] == LVX_NIL) {
        lmP->mgram[M-1].itemN--;
        continue;
      }

      /* Link the arrays */
      if (NGramLMFindMGram (lmP, M-1, lvX+1, &j) != M-1) {
        ERROR ("%d-gram table: index not found in line %d.\n", M, idx);
      } else if (j != lastj) {
        if (j < lastj && lastj > -1) {
	  int l;

	  /* when using e.g. the SRILM-Toolkit n-gram tables are not sorted
	     properly --> exit with TCL_CONTINUE and setting global variable
	     unsortedLM to 1 */
	  INFO ("NGramLMReadArpaboMGrams: unsorted %d-grams, switching to unsorted read.\n", M);
	  //WARN ("%d-gram table: problem (%d, %d) in line %d.\n", M, j, lastj, idx);
	  //WARN ("probably due to unsorted %d-grams -> switching to unsorted read.\n", M);
	  
	  /* Clear the m-gram table */
	  for (l = 0; l < lmP->order; l++)
	    NGramLMDeInitMGram (lmP, l);
	  free (lmP->mgram);
	  lmP->mgram = NULL;

	  /* Re-Init the unigram list */
	  NGramLMListReInit (lmP);

	  unsortedLM = 1;

	  return TCL_CONTINUE;
	}

        for (k = lastj + 1; k <= j; k++) {
          NJDSetLMLinkIdx (M-2, k, idx);
          if ((int)(NJDGetLMLinkIdx (M-2, k)) != idx) {
            /* ------------------------------------------------
                This is where we realize that we can't
                load the LM and try to reduce -segSize
               ------------------------------------------------ */
            int l;

            /* INFO ("\n%d-gram table: use '-segSize n' option, n < %d.\n", M, lmP->segSize); */

            /* Clear the m-gram table */
            for (l = 0; l < lmP->order; l++)
              NGramLMDeInitMGram (lmP, l);
            free (lmP->mgram);
            lmP->mgram = NULL;

            /* Re-Init the unigram list */
            NGramLMListReInit (lmP);

            return TCL_CONTINUE;
          }
        }
        lastj = j;
      }

    }

    p = atof (fieldP[0]); if ( p == lmP->log0 ) p = lmP->log0Val;
    lmP->mgram[M-1].probA[idx]      = CompressScore(p);
    if (M != lmP->order) {
      if ( fields == fieldN-1 ) {
	/* when using e.g. the SRILM-Toolkit empty back-off prob fields
	   can occur, which are here mapped to 0.0 */
	lmP->mgram[M-1].backoffA[idx] = CompressScore(0.0);
      } else {
	p = atof (fieldP[M+1]); if ( p == lmP->log0 ) p = lmP->log0Val;
	lmP->mgram[M-1].backoffA[idx] = CompressScore(p);
      }
    }
    if (M >  1)
      lmP->mgram[M-1].idA[idx]      = lvX[M];

    idx++;
  }

  if (M > 1) {
    for (k = lastj + 1; k <= lmP->mgram[M-2].itemN; k++)
      NJDSetLMLinkIdx (M-2, k, idx);
    lmP->mgram[M-1].idA[idx] = LVX_NIL;
  }

  /* Sanity checks */
  if (lmP->mgram[M-1].itemN != idx)
    INFO ( "Expected %d %d-grams but found %d.\n", lmP->mgram[M-1].itemN, M, idx);

  if (id) *id = lms;

  return TCL_OK;
}

#define MAX_NGRAM_ORDER_US 8

typedef struct {
  LVX     lvXA[MAX_NGRAM_ORDER_US];
  lmScore prob;
  lmScore backprob;
  int     idx;
} NGramLine;

static int cmpNGLines (const void *a, const void *b) {

  int res = 0;
  int i;

  for (i=0; i<unsortedLM_M; i++) {
    if ( ((NGramLine*)a)->lvXA[i] < ((NGramLine*)b)->lvXA[i] ) { res = -1; break; }
    if ( ((NGramLine*)a)->lvXA[i] > ((NGramLine*)b)->lvXA[i] ) { res =  1; break; }
  }

  return res;
}

/* only the section with 2-grams or higher are processed by that function,
   whereby the sort order is according to the unigram section */
static int NGramLMReadUnsortedArpaboMGrams (NGramLM* lmP, FILE* fP, int M, ArpaboLModelSection* id)
{
  ArpaboLModelSection lms;
  char          line[MAXLMLINE];
  char         *fieldP[1024];

  int           i, j, k, fields, fieldN;
  int           idx    = 0;
  int           lastj  = -1;
  NGramLine    *tmpA   = NULL;
  int           tmpN   = 0;
  int           X      = 0;
  float         p;

  /* How many fields should one line have? */
  fieldN = (M == lmP->order) ? M+1 : M+2;

  if ( lmP->order > MAX_NGRAM_ORDER_US ) {
    ERROR ("NGramLMReadUnsortedArpaboMGrams: increase MAX_NGRAM_ORDER_US\n");
    return TCL_ERROR;
  }

  /* allocate temporary array */
  if ( !(tmpA = (NGramLine*)malloc (lmP->mgram[M-1].itemN * sizeof (NGramLine))) ) {
    ERROR ("NGramLMReadUnsortedArpaboMGrams: allocation failure\n");
    return TCL_ERROR;
  }
  unsortedLM_M = M;

  /* Main loop */
  while (((lms = ArpaboLMReadLine (lmP, fP, line)) == LM_LINE) &&
         (idx < lmP->mgram[M-1].itemN)) {

    fields = scanArpaboLine (line, fieldP);

    idx++;

    if (fields != fieldN && fields != fieldN-1) {
      ERROR ("%d-gram table: line starting with '%s' invalid, skipping.\n", M, line);
      continue;
    }

    /* fill tmp array */
    for (i = 0; i < M; i++) {
      if ((j = NGramLMIndex (lmP, fieldP[i+1])) < 0) {
	ERROR ("%d-gram table: word '%s' not found, ignoring line.\n", M, fieldP[i]);
	break;
      } else {
	tmpA[X].lvXA[i] = (LVX)j;
      }
    }

    if ( i < M-1 ) {
      lmP->mgram[M-1].itemN--;
      continue;
    }

    p = atof (fieldP[0]); if ( p == lmP->log0 ) p = lmP->log0Val;
    tmpA[X].prob  = CompressScore (p);
    if ( M != lmP->order ) {
      if ( fields == fieldN-1 )
	/* when using e.g. the SRILM-Toolkit empty back-off prob fields
	   can occur, which are here mapped to 0.0 */
	tmpA[X].backprob = CompressScore (0.0);
      else {
	p = atof (fieldP[M+1]); if ( p == lmP->log0 ) p = lmP->log0Val;
	tmpA[X].backprob = CompressScore (p);
      }
    }
    tmpA[X].idx   = idx; /* arpabo-file-section line index */
    tmpN++;
    X++;

    /* if arpabo-file-header is wrong */
    if ( X == lmP->mgram[M-1].itemN )
      tmpA = (NGramLine*)realloc (tmpA, X * sizeof (NGramLine));
  }
  
  /* sorting the temporary array */
  qsort (tmpA, tmpN, sizeof(NGramLine), cmpNGLines);

  for (X=0; X<tmpN; X++) {

    /* Link the arrays */
    if (NGramLMFindMGram (lmP, M-1, tmpA[X].lvXA, &j) != M-1) {
      ERROR ("%d-gram table: index not found in line %d.\n", M, tmpA[X].idx);
    } else if (j != lastj) {
      if (j < lastj && lastj > -1)
	ERROR ("%d-gram table: problem (%d, %d) in line %d (X=%d).\n", M, j, lastj, tmpA[X].idx, X);
      for (k = lastj + 1; k <= j; k++) {
	NJDSetLMLinkIdx (M-2, k, X);
	if ((int)(NJDGetLMLinkIdx (M-2, k)) != X) {
	  /* --> trying to reduce -segSize */
	  int l;

	  /* Clear the m-gram table */
	  for (l = 0; l < lmP->order; l++)
	    NGramLMDeInitMGram (lmP, l);
	  free (lmP->mgram);
	  lmP->mgram = NULL;
	  
	  /* Re-Init the unigram list */
	  NGramLMListReInit (lmP);

	  /* mark, that this is a TCL_CONTINUE with reducing -segSize */
	  unsortedLM = 2;
	  if ( tmpA ) free (tmpA);

	  return TCL_CONTINUE;
	}
      }
      lastj = j;
    }
    
    lmP->mgram[M-1].probA[X]      = tmpA[X].prob;
    if (M != lmP->order)
      lmP->mgram[M-1].backoffA[X] = tmpA[X].backprob;
    if (M >  1)
      lmP->mgram[M-1].idA[X]      = tmpA[X].lvXA[M-1];
  }
  
  if (M > 1) {
    for (k = lastj + 1; k <= lmP->mgram[M-2].itemN; k++)
      NJDSetLMLinkIdx (M-2, k, X);
    lmP->mgram[M-1].idA[X] = LVX_NIL;
  }
  
  /* Sanity checks */
  if (lmP->mgram[M-1].itemN != X)
    INFO ( "Expected %d %d-grams but found %d.\n", lmP->mgram[M-1].itemN, M, X);
  
  if (id) *id = lms;

  if ( tmpA ) free (tmpA);
  
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMReadUnigramSection
   ------------------------------------------------------------------------ */

int NGramLMReadUnigramSection( NGramLM* lmP, FILE* fP, ArpaboLModelSection* id)
{
  char          line[MAXLMLINE];
  ArpaboLModelSection lms;
  int           n = 0;

  ERROR ("Reading Unigrams is not currently recommended!\n");

  while ((lms = ArpaboLMReadLine( lmP, fP, line)) == LM_LINE) {

    char  word[1024];
    float prob;
    //int   idx;

    /* ---------- */
    /* Parse line */
    /* ---------- */

    if ( sscanf( line, "%f %s", &prob, word) != 2) {
      if (line[0] == '\n' && line[0] == '\r')
	break;
      INFO("Format error; unigram ignored: '%s'", line);
    }

    /* ----------------------------- */
    /* Try to find word in NGramLM */
    /* ----------------------------- */

    if (NGramLMIndex( lmP, word) < 0) {
      ERROR("Word '%s' does not exists in '%s'.\n", word, lmP->lksP->name);
      continue;
    }
  }

  if ( id) *id = lms; 
  INFO("Read unigrams ugramN=%d.\n", n);
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMReadSubsSection
   ------------------------------------------------------------------------ */

static int NGramLMSubsItemInit (NGramLMSubs* sP, ClientData CD) {
  assert (sP);
  sP->line = (CD) ? strdup((char*)CD) : NULL;
  return TCL_OK;
}

static int NGramLMSubsItemDeInit (NGramLMSubs* sP) {
  if (!sP) return TCL_OK;
  if (sP->line) { free (sP->line); sP->line = NULL; }
  return TCL_OK;
}

static int NGramLMReadSubsSection (NGramLM* lmP, FILE* fP, ArpaboLModelSection* id)
{
  char                line[MAXLMLINE];
  ArpaboLModelSection lms;

  lmP->subslist.init    = (ListItemInit  *)NGramLMSubsItemInit;
  lmP->subslist.deinit  = (ListItemDeinit*)NGramLMSubsItemDeInit;

  while ((lms = ArpaboLMReadLine (lmP, fP, line)) == LM_LINE) {
    line[strlen(line)-1] = '\0';
    listIndex((List*)&(lmP->subslist), line, 1);
  }

  if (id) *id = lms; 
  return TCL_OK;
}


/* ========================================================================
    NGramLMRead
   ---------------
    Reads in an ARPABO language model file
    Substitutions get stored in the NGramLM object, where the vocabulary
    mapper can get at them
   ======================================================================== */

int NGramLMReadArpabo (NGramLM* lmP, FILE* fp, char *txt, int quant)
{
  char                      line[MAXLMLINE];
  ArpaboLModelSection       lms;
  int             section = 0;
  int                  rc = TCL_OK;
  FILE*                fP = NULL;

  /* HACK */
  quant = lmP->quantize;

  strncpy (line, txt, MAXLMLINE-1);
  while ((lms = ArpaboLMReadLine (lmP, fP, line)) == LM_LINE) fP = fp;

  if (!fP) fP = fp;

  /* ====================================
      Main loop
     ==================================== */
  while (lms != LM_END && rc == TCL_OK) {

    switch (lms) {

    case LM_DATA :
      rc = NGramLMReadArpaboMGramCounts (lmP, fP, &lms);
      /* INFO (""); */
      section = 1;
      break;

    case LM_NGRAMS :

      if (!section) {
	WARN ("Found NGrams before data mark.\n");
	lms = ArpaboLMReadLine( lmP, fP, line);
      } else if (section == NGramLMReadLine_N) {
	section++;
	if ( unsortedLM > 0 && NGramLMReadLine_N > 1 ) {
	  rc = NGramLMReadUnsortedArpaboMGrams (lmP, fP, NGramLMReadLine_N, &lms);
	} else {
	  rc = NGramLMReadArpaboMGrams    (lmP, fP, NGramLMReadLine_N, &lms);
	}

	/* fprintf (stderr, "(%dG:", NGramLMReadLine_N); 
	   if ((rc = NGramLMReadArpaboMGrams (lmP, fP, NGramLMReadLine_N, &lms)) == TCL_OK)
	   fprintf (stderr, "%d)", lmP->mgram[section-2].itemN);
	*/

      } else {
	ERROR ("%d-gram section expected, found %d.\n", section, NGramLMReadLine_N);
	rc = TCL_ERROR;
      }
      break;

    case LM_UNIGRAMS :

      /* fprintf (stderr, "(0G:???"); */
      rc = NGramLMReadUnigramSection( lmP, fP, &lms);
      break;

    case LM_SUBS :

      /* fprintf (stderr, "(Subs:"); */
      rc = NGramLMReadSubsSection( lmP, fP, &lms);
      /* fprintf (stderr, "%d)", lmP->subslist.itemN); */
      break;

    default :

      lms = ArpaboLMReadLine( lmP, fP, line);

    }
  }

  /* ==========================================================
      Ok, finish loading the LM
     ========================================================== */
  if (rc == TCL_OK) {
    if (quant == 0) quant = lmP->order - 1;
    if (quant <  1) quant = 1;
    for (section = quant; section < lmP->order - 1; section++) {
      compressProbs    (lmP, section);
      compressBackoffs (lmP, section);
    }
    if (quant == lmP->order - 1)
      compressProbs    (lmP, lmP->order - 1);

    if (lmP->order < 1)
    WARN ("Hm, are you sure this is an %d-gram ARPABO-file?\n", lmP->order);
  }

  return rc;
}

/* ========================================================================
    NGramLMDump
   ---------------
    Dumps an LM to a machine-independent dump-file format,
    or a machine-dependent format suitable for reading with mmap()
   ======================================================================== */

static int filealign (FILE* fp) {
  long p = ftell (fp) % 8;
  if (p) p = 8-p;
  while (p--)
    fwrite (&p, sizeof (char), 1, fp);
  return 0;
}

int NGramLM2MMap (LingKS *lksP, FILE* fp)
{
  NGramLM     *lmP = (NGramLM*) lksP->data.ngramLM;
  int          i = 1;

  /* Hello, world! */
  write_string (fp, "LMODELNJD-MMAPI");
  filealign (fp);
  fwrite (&i, sizeof (int), 1, fp); /* to check endianness */

  /* Basic parameters */
  fwrite (&lmP->order, sizeof (int), 1, fp);
  fwrite (&lmP->history, sizeof (int), 1, fp);
  fwrite (&lmP->segSize, sizeof (int), 1, fp);
  fwrite (&lmP->list.itemN, sizeof (int), 1, fp);
  INFO ("Creating mmap for %d-gram model, segSize=%d, itemN=%d.\n", lmP->order, lmP->segSize, lmP->list.itemN);

  /* Some checks */
  i = sizeof (LVX);
  fwrite (&i, sizeof (int), 1, fp);
  i = sizeof (lmScore);
  fwrite (&i, sizeof (int), 1, fp);

  /* Names of words (unigram entries) */
  for (i = 0; i < lmP->list.itemN; i++)
    write_string (fp, lmP->list.itemA[i].name);

  /* M-Grams */
  for (i = 0; i < lmP->order; i++) {
    MGram* mg = lmP->mgram + i;
    filealign (fp);

    fwrite (&mg->itemN, sizeof (int), 1, fp);
    if (mg->cprobA) {
      int v1 = 1;
      fwrite (&v1, sizeof (int), 1, fp);
      fwrite (mg->cprobA, sizeof (char), mg->itemN, fp);
      filealign (fp);
      fwrite (mg->probA, sizeof (lmScore), 256, fp);
    } else {
      int v0 = 0;
      fwrite (&v0, sizeof (int), 1, fp);
      fwrite (mg->probA, sizeof (lmScore), mg->itemN, fp);
    }
    
    if (i != lmP->order - 1) {
      filealign (fp);
      if (mg->cbackoffA) {
	int v1 = 1;
	fwrite (&v1, sizeof (int), 1, fp);
	fwrite (&mg->cbackoffA, sizeof (char), mg->itemN, fp);
	filealign (fp);
	fwrite (mg->backoffA, sizeof (lmScore), 256, fp);
      } else {
	int v0 = 0;
	fwrite (&v0, sizeof (int), 1, fp);
	fwrite (mg->backoffA, sizeof (lmScore), mg->itemN, fp);
      }    

      filealign (fp);
      fwrite (mg->segTbl, sizeof (int), ((mg->itemN+1)>>(lmP->segSize))+1, fp);
      fwrite (mg->linkA, sizeof (LVX), mg->itemN+1, fp);
    }

    if (i) {
      filealign (fp);
      fwrite (mg->idA, sizeof (LVX), mg->itemN+1, fp);
    }
  }

  /* Bye, bye */
  write_string (fp, "LMODELNJD-END");

  return TCL_OK;
}

static int mgramSave (NGramLM* lmP, int m, FILE* fp)
{
  MGram* mg = lmP->mgram+m;
  char    s[MAXLMLINE];

  sprintf (s, "%dGRAM-BEGIN", m+1);
  write_string (fp, s);

  write_int (fp, mg->itemN);

  if (mg->cprobA) {
    write_int (fp, 1);
    fwrite (mg->cprobA, sizeof (char), mg->itemN, fp);
#ifdef COMPRESSEDLM
    if (sizeof(lmScore)==sizeof(short))
      write_shorts (fp, (short*)mg->probA, 256);
    else
      fwrite (mg->probA, sizeof(char), 256, fp); 
#else
    write_floats (fp, mg->probA, 256);
#endif
  } else {
    write_int (fp, 0);
#ifdef COMPRESSEDLM
    if (sizeof(lmScore)==sizeof(short))
      write_shorts (fp, (short*)mg->probA, mg->itemN);
    else
      fwrite (mg->probA, sizeof(char), mg->itemN, fp); 
#else
    write_floats (fp, mg->probA, mg->itemN);
#endif
  }

  if (m != lmP->order - 1) {
    if (mg->cbackoffA) {
      write_int (fp, 1);
      fwrite (mg->cbackoffA, sizeof (char), mg->itemN, fp);
#ifdef COMPRESSEDLM
      if (sizeof(lmScore)==sizeof(short))
	write_shorts (fp, (short*)mg->backoffA, 256);
      else
	fwrite (mg->backoffA, sizeof(char), 256, fp); 
#else
      write_floats (fp, mg->backoffA, 256);
#endif
    } else {
      write_int (fp, 0);
#ifdef COMPRESSEDLM
      if (sizeof(lmScore)==sizeof(short))
	write_shorts (fp, (short*)mg->backoffA, mg->itemN);
      else
	fwrite (mg->backoffA, sizeof(char), mg->itemN, fp); 
#else
      write_floats (fp, mg->backoffA, mg->itemN);
#endif
    }    

    if (sizeof(LVX) == sizeof(short)) 
      write_shorts (fp, (short*) mg->linkA,  mg->itemN);
    else
      write_ints   (fp, (int*)   mg->linkA,  mg->itemN);
    write_ints   (fp, (int*)   mg->segTbl, ((mg->itemN+1)>>(lmP->segSize))+1);
  }

  if (m) {
    if (sizeof(LVX) == sizeof(short)) 
      write_shorts (fp, (short*) mg->idA,    mg->itemN);
    else
      write_ints   (fp, (int*)   mg->idA,    mg->itemN);
  }

  write_string (fp, "MGRAM-END");

  return TCL_OK;
}

int NGramLMSave (LingKS *lksP, FILE* fp)
{
  NGramLM     *lmP = (NGramLM*)lksP->data.ngramLM;
  int          i;

  /* Hello, world! */
  write_string (fp, "LMODELNJD-BEGIN");

  /* Basic parameters */
  write_int (fp, lmP->order);
  write_int (fp, lmP->history);
  write_int (fp, lmP->segSize);
  write_int (fp, lmP->list.itemN);

  /* Names of words (unigram entries) */
  for (i = 0; i < lmP->list.itemN; i++)
    write_string (fp, lmP->list.itemA[i].name);

  /* M-Grams */
  for (i = 0; i < lmP->order; i++)
    mgramSave (lmP, i, fp);

  /* Substitutions section */
  if (lmP->subslist.itemN) {
    write_string   (fp, "LMODELNJD-SUBSLIST");
    write_int      (fp, lmP->subslist.itemN);
    for (i = 0; i < lmP->subslist.itemN; i++)
      write_string (fp, lmP->subslist.itemA[i].line);
  }

  /* Bye, bye */
  write_string (fp, "LMODELNJD-END");

  return TCL_OK;
}

int NGramLMSaveItf (ClientData cd, int argc, char *argv[]) {

  NGramLM *lmP  = (NGramLM*)cd;
  int      ac   = argc - 1;
  char    *name = NULL;
  FILE    *fp   = NULL;
  int      res  = TCL_OK;
  int      mmap = 0;

  if (itfParseArgv (argv[0], &ac, argv+1, 0,
      "<filename>", ARGV_STRING, NULL, &name, NULL, "file to save (dump) LM to",
      "-mmap",      ARGV_INT,    NULL, &mmap, NULL, "save as MMAP-type dump",
      NULL) != TCL_OK) return TCL_ERROR;

  if ( !(fp = fileOpen (name, "w")) ) {
    ERROR ("Could not open '%s' for writing.\n", name);
    return TCL_ERROR;
  }

  if (mmap) res = NGramLM2MMap (lmP->lksP, fp);
  else      res = NGramLMSave  (lmP->lksP, fp);

  fileClose (name, fp);

  return res;
}


/* ========================================================================
    NGramLMReadDump
   -------------------
    Reads an LM from a machine-independent dump-file format,
    or a machine-dependent mmap()
   ======================================================================== */

static int fileAlign (FILE* fp) {
  long p = ftell (fp) % 8;
  if (p) fseek (fp, 8-p, SEEK_CUR);
  return 0;
}

void* memAlign (void* p) {
  if (((long)p)%8) p += 8-(((long)p)%8);
  return p;
}

int NGramLMMMap (NGramLM *lmP, FILE* fp, char *file)
{
  char       str[MAXLMLINE];
  int   i, itemM;
  long pa, p1, pe;
  char* p;

#ifdef WINDOWS
  WARN ("MMap not supported under Windows\n");
  return TCL_ERROR;
#else

  if (lmP->mmapP) {
    WARN ("Mapping already exists, ignoring.\n");
    return TCL_ERROR;
  }

  /* Basics */
  fileAlign (fp);
  fread (&i, sizeof (int), 1, fp); /* to check reading */
  if (i != 1)
    WARN ("This does not look good.\n");

  fread (&lmP->order, sizeof (int), 1, fp);
  fread (&lmP->history, sizeof (int), 1, fp);
  fread (&lmP->segSize, sizeof (int), 1, fp);
  fread (&itemM, sizeof (int), 1, fp);
  //INFO ("MMapping %d-gram model, segSize=%d, itemN=%d.\n", lmP->order, lmP->segSize, itemM);
  lmP->mgram   = (MGram*) malloc (sizeof (MGram) * lmP->order);

  /* Some checks */
  fread (&i, sizeof (int), 1, fp);
  if (i != sizeof (LVX)) {
    ERROR ("This dump was written with size of LVX=%d, aborting\n", i);
    return TCL_ERROR;
  }
  fread (&i, sizeof (int), 1, fp);
  if (i != sizeof (lmScore)) {
    ERROR ("This dump was written with size of lmScore=%d, aborting\n", i);
    return TCL_ERROR;
  }

  /* Names of words (unigram entries) */
  for (i = 0; i < itemM; i++) {
    int idx;
    read_string (fp, str);
    if (i != (idx = listNewItem ((List*)&(lmP->list), (ClientData) str))) {
      ERROR ("Word '%s' got wrong index %d (not %d).\n", str, idx, i);
      continue;
    }
    lmP->list.itemA[idx].lmP = lmP;
  }

  /* so far reading was pretty standard (apart from alignment) */
  fileAlign (fp);
  p1 = ftell (fp); fseek (fp, 0,  SEEK_END);
  pe = ftell (fp); fseek (fp, p1, SEEK_SET);
  pa = p1 - (p1 % sysconf(_SC_PAGE_SIZE)); /* for alignment */

  /* create the mapping */
  lmP->mmapP = mmap (lmP->mmapP, pe-pa, PROT_READ, MAP_SHARED, fileno (fp), pa);
  if ((void*) lmP->mmapP == MAP_FAILED) {
    WARN ("MMapping failed, don't know why\n");
    return TCL_ERROR;
  }
  lmP->mmapS = pe-pa;
  p = (char*) lmP->mmapP + p1-pa;

  /* M-Grams */
  for (i = 0; i < lmP->order; i++) {
    MGram* mg = lmP->mgram + i;
    int itemN, X;
    char* pp;
    
    pp = p = memAlign (p);
    itemN = *((int*)p), p += sizeof (int);
    X     = *((int*)p), p += sizeof (int);

    mg->itemN = itemN;
    if (X) {
      /* highest-order m-gram */
      mg->cprobA = (unsigned char*) p, p += itemN * sizeof (char);
      p = memAlign (p);
#ifdef COMPRESSEDLM
      mg->probA  = (lmScore*) p, p += 256 * sizeof (lmScore);
#else
      mg->probA  = (float*)   p, p += 256 * sizeof (float);
#endif
    } else {
      mg->cprobA = NULL;
#ifdef COMPRESSEDLM
      mg->probA  = (lmScore*) p, p += itemN * sizeof (lmScore);
#else
      mg->probA  = (float*)   p, p += itemN * sizeof (float);
#endif
    }

    if (i != lmP->order - 1) {
      p = memAlign (p);
      X = *((int*)p), p += sizeof (int);
      if (X) {
	mg->cbackoffA = (unsigned char*) p, p += itemN * sizeof (char);
	p = memAlign (p);
#ifdef COMPRESSEDLM
	mg->backoffA = (lmScore*) p, p += 256 * sizeof (lmScore);
#else
	mg->backoffA = (float*)   p, p += 256 * sizeof (float);
#endif
      } else {
	mg->cbackoffA = NULL;
#ifdef COMPRESSEDLM
	mg->backoffA = (lmScore*) p, p += itemN * sizeof (lmScore);
#else
	mg->backoffA = (float*)   p, p += itemN * sizeof (float);
#endif
      }
  
      p = memAlign (p);
      mg->segTbl = (unsigned int*) p, p += (((itemN+1)>>(lmP->segSize))+1) * sizeof (int);
      mg->linkA  = (LVX*) p, p += (itemN+1) * sizeof (LVX);
    }
    
    if (i) {
      p = memAlign (p);
      mg->idA = (LVX*) p, p += (itemN+1) * sizeof (LVX);
    }
  }
    
  /* Bye, bye */
  fseek (fp, 0, SEEK_END);
  if (strcmp (p+2, "LMODELNJD-END"))
    WARN ("End marker not found in dump file.\n");

  return TCL_OK;
#endif
}

static int mgramField (void* a, FILE* fp, int l)
{
#ifdef COMPRESSEDLM
  if (sizeof(lmScore)==sizeof(short))
    read_shorts (fp, (short*)a, l);
  else
    fread (a, sizeof(char), l, fp); 
#else
  if (!compressedLM) {
    /* Default code */
    read_floats (fp, a, l);
  } else {
    /* This code can be used as a hack to read compressed LM dumps
       into an uncompressed structure. Use at your own risk */
    short* tmp = (short*) malloc (sizeof (short) * l);
    float* A = (float*)a;
    int i;

    read_shorts (fp, (short*)tmp, l);
    for (i = 0; i < l; i++)
      A[i] = .001*tmp[i];
    free (tmp);
  }
#endif
  return 0;
}

static int mgramLoad (NGramLM* lmP, int m, FILE* fp)
{
  MGram* mg = lmP->mgram+m;
  int itemN;
  char str[512], str2[512];

  /* Consistency checks */
  read_string (fp, str);
  sprintf (str2, "%dGRAM-BEGIN", m+1);
  if (strcmp (str, str2)) {
    ERROR ("Inconsistent file.\n");
    return TCL_ERROR;
  }

  itemN = read_int (fp);
  NGramLMInitMGram (lmP, m, itemN);

  if (read_int (fp)) {
    /* highest-order m-gram */
    mg->cprobA = (unsigned char*) realloc (mg->cprobA, sizeof (char)    * itemN);
    mg->probA  = (lmScore*)       realloc (mg->probA,  sizeof (lmScore) * 256);
    fread (mg->cprobA, sizeof (char), itemN, fp);
    mgramField ((void*) mg->probA, fp, 256);
  } else {
    mgramField ((void*) mg->probA, fp, itemN);
  }

  if (m != lmP->order - 1) {
    if (read_int (fp)) {
      mg->cbackoffA = (unsigned char*) realloc (mg->cbackoffA, sizeof (char)    * itemN);
      mg->backoffA  = (lmScore*)       realloc (mg->backoffA,  sizeof (lmScore) * 256);
      fread (mg->cbackoffA, sizeof (char), itemN, fp);
      mgramField ((void*) mg->backoffA, fp, 256);
    } else {
      mgramField ((void*) mg->backoffA, fp, itemN);
    }
    if (upsampledLM) {
      unsigned short *_mgA = malloc (itemN*sizeof(unsigned short)); /* 16 bit LVX type */
      int i;
      read_shorts (fp, (short*) _mgA, itemN);
      for (i = 0; i < itemN; i++)
	mg->linkA[i] = (LVX) _mgA[i];
      free (_mgA);
    } else if (sizeof(LVX) == sizeof(short))
      read_shorts (fp, (short*) mg->linkA,  itemN);
    else
      read_ints   (fp, (int*)   mg->linkA,  itemN);

    read_ints   (fp, (int*)   mg->segTbl, ((itemN+1)>>(lmP->segSize))+1);
  }

  if (m) {
    if (upsampledLM) {
      unsigned short *_mgA = malloc (itemN*sizeof(unsigned short)); /* 16 bit LVX type */
      int i;
      read_shorts (fp, (short*) _mgA, itemN);
      for (i = 0; i < itemN; i++)
	mg->idA[i] = (LVX) _mgA[i];
      free (_mgA);
    } else if (sizeof(LVX) == sizeof(short))
      read_shorts (fp, (short*) mg->idA, itemN);
    else 
      read_ints   (fp, (int*)   mg->idA, itemN);

    /* Why, oh why, did we not do this in the first place */
    lmP->mgram[m-1].linkA[lmP->mgram[m-1].itemN] =
      (LVX) (itemN - lmP->mgram[m-1].segTbl[lmP->mgram[m-1].itemN>>lmP->segSize]);
  }

  /* Bye, bye */
  /* read_string (fp, str); */
  itemN = read_short(fp);
  if (itemN <= 0 || itemN > 511) {
    if (upsampledLM || sizeof(LVX) == sizeof(short)) {
      WARN ("mgramLoad: trying reading as compressed LM\n");
      compressedLM = 1;
      return TCL_CONTINUE;
    } else {
      WARN ("mgramLoad: trying reading with |LVX|==|short|\n");
      upsampledLM = 1;
      return TCL_CONTINUE;
    }
  }
  fread (str, itemN+1, 1, fp);
  if (strcmp (str, "MGRAM-END")) {
    ERROR ("mgramLoad: inconsistent dump file.\n");
    return TCL_ERROR;
  }

  return TCL_OK;
}

int NGramLMLoad_ (NGramLM *lmP, FILE* fp, char *txt)
{
  int   i, itemN, ok = TCL_OK;
  char       str[MAXLMLINE];

  /* Consistency checks */
  if (!fp) {
    ERROR ("Invalid file pointer.\n");
    return TCL_ERROR;
  }

  if (!txt) {
    read_string (fp, str);
    if (strcmp (str, "LMODELNJD-BEGIN")) {
      ERROR ("Inconsistent file.\n");
      return TCL_ERROR;
    }
  }

  /* Basics */
  lmP->order   = read_int (fp);
  lmP->history = read_int (fp);
  lmP->segSize = read_int (fp);
  itemN        = read_int (fp);
  lmP->mgram   = (MGram*) malloc (sizeof (MGram) * lmP->order);

  if (LVX_MAX < itemN) {
    ERROR ("NGramLMLoad: LVX_MAX=%d < itemN=%d -- won't work\n", LVX_MAX, itemN);
    free (lmP->mgram);
    lmP->mgram = NULL;
    return TCL_ERROR;
  }

  /* Names of words (unigram entries) */
  for (i = 0; i < itemN; i++) {
    int idx;
    read_string (fp, str);
    if (i != (idx = listNewItem ((List*)&(lmP->list), (ClientData) str))) {
      ERROR ("Word '%s' got wrong index %d (not %d).\n", str, idx, i);
      continue;
    }
    lmP->list.itemA[idx].lmP = lmP;
  }

  /* M-Grams */
  for (i = 0; i < lmP->order && ok == TCL_OK; i++)
    ok = mgramLoad (lmP, i, fp);
  if (ok == TCL_ERROR)
    return TCL_ERROR;
  if (ok != TCL_OK) {
    /* Clear the m-gram table */
    while (--i >= 0) NGramLMDeInitMGram (lmP, i);
    free (lmP->mgram);
    lmP->mgram = NULL;
    
    /* Re-Init the unigram list */
    NGramLMListReInit (lmP);

    return TCL_CONTINUE;
  }

  /* Subsection?  */
  read_string (fp, str);
  if (streq  (str, "LMODELNJD-SUBSLIST")) {
    int number = read_int (fp);

    lmP->subslist.init    = (ListItemInit  *) NGramLMSubsItemInit;
    lmP->subslist.deinit  = (ListItemDeinit*) NGramLMSubsItemDeInit;

    for (i = 0; i < number; i++) {
      read_string (fp, str);
      listIndex ((List*)&(lmP->subslist), str, 1);
    }

    read_string (fp, str);
  }

  /* Bye, bye */
  if (strcmp (str, "LMODELNJD-END")) {
    ERROR ("Inconsistent file.\n");
    return TCL_ERROR;
  }

  return TCL_OK;
}

int NGramLMLoad (LingKS *lksP, FILE* fp, char* txt)
{
  NGramLM *lmP = (NGramLM*)lksP->data.ngramLM;

  char line[MAXLMLINE];
  int r = TCL_ERROR;

  switch (idFile (fp, line)) {
  case ID_DUMP:
    r = NGramLMLoad_ (lmP, fp, line);
    break;
  case ID_MMAPI:
    r = NGramLMMMap (lmP, fp, txt);
    break;
  default:
    if ((r = NGramLMReadArpabo (lmP, fp, line, 0)) == TCL_CONTINUE) {
      /* unsortedLM == 0 => we're fine
	               1 => sort in next try (keep segSize)
		       2 => tried sorting, doesn't help, maybe decrease segSize */
      if (unsortedLM != 1)
	lmP->segSize--;
      if (lmP->segSize < 1) {
	ERROR ("NGramLMLoad: segSize == 0, NGramLM too big\n");
	r = TCL_ERROR;
      }
    }
    break;
  }
  
  if (r == TCL_OK && lmP->history > (int) sizeof(LCT)/(int) sizeof(LVX)) {
    INFO ("NGramLMLoad: switching to hashed LCTs for LM of history=%d\n", lmP->history);
    lmP->hash = 1;
    NGramLMHashStatus (lmP);
  }

  return r;
}

static int NGramLMLoadItf (ClientData cd, int argc, char *argv[]) {

  NGramLM *lmP      = (NGramLM*)cd;
  char    *name     = NULL;
  int      ac       = argc - 1;
  int      r        = 0;
  FILE    *fp       = NULL;
  int      quantize = 0;
  int      segSize  = 0;
  int      retried  = 0;

  unsortedLM        = 0;
  upsampledLM       = 0;
  compressedLM      = 0;

  if (itfParseArgv(argv[0], &ac, argv+1, 0, 
      "<filename>", ARGV_STRING, NULL, &name,       cd,   "file to read from", 
      "-noquant",   ARGV_INT,    NULL, &quantize,   NULL, "do not quantize up to n-Gram x",
      "-segSize",   ARGV_INT,    NULL, &segSize,    NULL, "re-configure segment size",
      "-unsorted",  ARGV_INT,    NULL, &unsortedLM, NULL, "read LMs with unsorted n-gram sections, e.g. SRILM-Format",
      NULL) != TCL_OK) return TCL_ERROR;

  if (segSize)  lmP->segSize  = segSize;
  if (quantize) lmP->quantize = quantize;

  segSize = lmP->segSize;

  /* Try to open the file */
  if ( !(fp = fileOpen (name, "r")) ) {
    ERROR ("Cannot open file '%s' for reading.\n", name);
    return TCL_ERROR;
  }

  /* The loading function may want to be called again,
     for example NGramLM can automatically reduce 'segSize' */
  while ((r = NGramLMLoad (lmP->lksP, fp, name)) == TCL_CONTINUE) {
    fileClose (name, fp);
    fp = fileOpen (name, "r");
    if ( unsortedLM != 1 ) retried = 1;
  }
  fileClose (name, fp);

  if (retried)
    INFO ("ngramLMLoad: configured -segSize to %d.\n", lmP->segSize);

  return r;
}

/* ------------------------------------------------------------------------
    NGramLMReadVocab - Read Vocabfile
   ------------------------------------------------------------------------ */

static int NGramLMReadVocab(NGramLM* lmP, char* fileName) {
  FILE*               fp = NULL;
  char*            lineP = malloc(sizeof(char)*MAXLMLINE);
  char*         linePorg = lineP;

  if ( !(fp = fileOpen (fileName, "r")) ) {
    ERROR ("Cannot open file '%s' for reading.\n", fileName);
    return TCL_ERROR;
  }

  /* Remove end of line from string */
  while (fgets(lineP, MAXLMLINE-1, fp)) {
    while(*lineP != '\0') {
      if (*lineP == '\n') *lineP = '\0';
      lineP++;
    }
    lineP=linePorg;
    listNewItem((List*)&(lmP->list), (ClientData)lineP);
  }

  return TCL_OK;
}

static int NGramLMReadVocabItf(ClientData cd, int argc, char *argv[]) {
  NGramLM *lmP      = (NGramLM*)cd;
  int      ac       = argc - 1;
  char    *fileName = NULL;

  if (itfParseArgv(argv[0], &ac, argv+1, 0, 
      "<filename>", ARGV_STRING, NULL, &fileName, cd, "file to read the vocab from", 
        NULL) != TCL_OK) return TCL_ERROR;

  return NGramLMReadVocab(lmP, fileName);
}


/* ========================================================================
    NGramLMScoreServer
   -------------------
    Stuff for extern ScoreServer
   ======================================================================== */

/* ------------------------------------------------------------------------
    NGramLMDisconnectSriServer - Disconnecting from a NGram-Score-Server
                                 and cleaning up
   ------------------------------------------------------------------------ */

static int NGramLMDisconnectSriServer (NGramLM *lmP) {

  /* Close the socket */
  if (Tcl_Close(itf, lmP->remoteChannel) != TCL_OK) {
    ERROR ("Error disconnecting from sri server\n");
    return TCL_ERROR;
  }

  /* Clear channel and restore the score function */
  lmP->remoteChannel       = NULL;
  lmP->lksP->scoreFct      = NGramLMScore;
  lmP->lksP->scoreArrayFct = NGramLMScoreArray;

  listDeinit( (List*) &(lmP->ngspCL));
  free( currNGSP.ngram );

  listDeinit( (List*) &(lmP->lctapCL));

  /* Free allocated memory for cachelists*/
  Tcl_DStringFree(SRIdstrPtr);
  free(SRIdstrPtr);
  TclFreeObj(SRIstrObjPtr);

  INFO("NGSPCL:  %d cache hits, %d cache misses\n", sri_cache_hit, sri_cache_miss);
  INFO("LCTAPCL: %d cache hits, %d cache misses\n", lcta_cache_hit, lcta_cache_miss);

  return TCL_OK;
}


static int NGramLMDisconnectSriServerItf (ClientData cd, int argc, char *argv[]) {
  NGramLM *lmP      = (NGramLM*) cd;
  int      ac       = argc - 1;

  if (itfParseArgv(argv[0], &ac, argv+1, 0, 
        NULL) != TCL_OK) return TCL_ERROR;

  return  NGramLMDisconnectSriServer(lmP);
}


/* ========================================================================
    NGramLM - CacheList - Stuff
   ======================================================================== */

/* ------------------------------------------------------------------------
    NGramLMNGSPCacheList functions
   ------------------------------------------------------------------------ */

/* compute hashkey */
static long hashNGSPKey(NGramScorePair* ngsp ) {
  char*       ngram1 = (char*) ngsp->ngram;
  unsigned long hash = 0;

  while ( *ngram1) {
      hash = ((hash << 5) | (hash >> (8*sizeof(long)-5))) ^ *ngram1;
      ++ngram1;
    }
  return (hash);
}

/* compare two NGSP */
static int hashNGSPCmp(NGramScorePair* ngsp1, NGramScorePair* ngsp2) {
  char* s1 = ngsp1->ngram;
  char* s2 = ngsp2->ngram;
 
  while( *s1 != '\0' )
    if ( *(s1++) != *(s2++)) return 0;
  return (*s2=='\0');
}

/* initialize new NGSPListItem */
int NGSPListItemInit( NGramScorePair* destP, NGramScorePair* ngsp ) {
  assert(destP);
  if ( !destP->ngram ) destP->ngram = (char*) malloc( 200 * sizeof(char));
  strcpy( destP->ngram, ngsp->ngram);
  destP->prob  = (ngsp) ? ngsp->prob : 0.0;
  return TCL_OK;
}

/* deinit and free memory in NGramLMNGSPCacheList */
int NGSPListItemDeinit( NGramScorePair* ngsp) {
  if ( !ngsp ) return TCL_OK;
  if ( ngsp->ngram ) { 
    free( ngsp->ngram ); 
    ngsp->ngram = NULL;
  }
  return TCL_OK;
}

/* ------------------------------------------------------------------------
    NGramLMLCTAPCacheList - Functions
   ------------------------------------------------------------------------ */


/* compute hashKey */
static long hashLCTAPKey( NGramLCTAPair* lctap ) {
  return lctap->lct;
}

/* compare hashKeys */
static int hashLCTAPCmp ( NGramLCTAPair* lctap1, NGramLCTAPair* lctap2 ) {
  return (lctap1->lct == lctap2->lct);
}

/* initialize new LCTAPListItem */
int LCTAPListItemInit ( NGramLCTAPair* destP, NGramLCTAPair* lctap ) {
  /* int i; */
  assert(destP);
  destP->lct   = lctap->lct;
  destP->itemN = lctap->itemN;
  destP->arr = (lmScore*) realloc( destP->arr, (lctap->itemN) * sizeof(lmScore));

  /*  for ( i = 0; i<lctap->itemN; i++ ) { destP->arr[i] = lctap->arr[i]; }*/

  memcpy( destP->arr, lctap->arr, lctap->itemN * sizeof(lmScore));
  return TCL_OK;
}

/* deinit and free memory in NGramLMLCTAPCacheList */
int LCTAPListItemDeinit( NGramLCTAPair* lctap ) {
  free(lctap->arr);
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMConnectSriServer - Connecting to a NGram-Score-Server
   ------------------------------------------------------------------------ */

static int NGramLMConnectSriServer (NGramLM *lmP, char *server, int port, int order, char *vocabF) {
  Tcl_Channel channel = NULL;                       /* The channel created for communication */
  SRIdstrPtr = malloc(sizeof(*SRIdstrPtr));
  SRIstrObjPtr = Tcl_NewStringObj("",0);

  /* Open socket to SRI LM Server */
  if ((channel =  Tcl_OpenTcpClient(itf, port, server, NULL, 0, 0)) == NULL) {
    ERROR("Unable to connect to SRI LM server at host %s port %d\n", server, port);
    return TCL_ERROR;
  }
  Tcl_SetChannelOption(itf, channel, "-translation", "lf");


  /* Store channel and change the score function */
  lmP->remoteChannel       = channel;
  lmP->lksP->scoreFct      = NGramLMScoreSriLMServer;
  lmP->lksP->scoreArrayFct = NGramLMScoreArraySriLMServer;

  /* read vocab if given and set lm order */
  if(vocabF) {
    if (NGramLMReadVocab(lmP, vocabF) != TCL_OK) {
      ERROR("Could not read vocab file '%s' while connecting to SRI LM server\n", vocabF);
      return TCL_ERROR;
    }
  }
  lmP->order   = order;
  lmP->history = order-1;

  if (lmP->order < 1)
    WARN ("Hm, are you sure this is an %d-gram ARPABO-file?\n", lmP->order);
  else if (lmP->history > (int) sizeof(LCT)/(int) sizeof(LVX)) {
    INFO ("Switching to Hashed LCTs for this %d-gram LM with history %d.\n", lmP->order, lmP->history);
    lmP->hash = 1;
    NGramLMHashStatus (lmP);
  }

  /* Get the answer from the SRI LM server */
  Tcl_DStringInit(SRIdstrPtr);
  Tcl_Gets(channel, SRIdstrPtr);
  INFO("SRI LM Server answered: '%s'\n", Tcl_DStringValue(SRIdstrPtr));

  /* Initialize NGSP-CacheList */
  if ( listInit ((List*) &(lmP->ngspCL), NULL, sizeof(NGramScorePair), 10000) != TCL_OK) {
    ERROR ("Couldn't allocate NGramLMNGSPCacheList!");
    return TCL_ERROR;
  }
  /* define ngspCL-functions */
  lmP->ngspCL.hashKey  = (HashKeyFn *) hashNGSPKey;
  lmP->ngspCL.hashCmp  = (HashCmpFn *) hashNGSPCmp;
  lmP->ngspCL.init     = (ListItemInit *) NGSPListItemInit;
  lmP->ngspCL.deinit   = (ListItemDeinit *) NGSPListItemDeinit;
  lmP->ngspCL.itemMax  = 10000;
  INFO("NGSPCL-ITEMMAX = %d\n", lmP->ngspCL.itemMax);
  currNGSP.ngram = (char*) malloc( (order+1) * MAXLMLINE * sizeof( char )); 


  /* Initialize LCTAP-CacheList */
  if ( listInit((List*) &(lmP->lctapCL), NULL, sizeof(NGramLCTAPair), 10000) != TCL_OK) {
    ERROR ("Couldn't allocate NGramLMLCTAPCacheList!\n");
    return TCL_ERROR;
  }
  /* define lctapCL-functions */
  lmP->lctapCL.hashKey  = (HashKeyFn *) hashLCTAPKey;
  lmP->lctapCL.hashCmp  = (HashCmpFn *) hashLCTAPCmp;
  lmP->lctapCL.init     = (ListItemInit *) LCTAPListItemInit;
  lmP->lctapCL.deinit   = (ListItemDeinit *) LCTAPListItemDeinit;
  lmP->lctapCL.itemMax  = 1000;
  INFO("LCTAPCL-ITEMMAX = %d\n", lmP->lctapCL.itemMax);

  return TCL_OK;
}


static int NGramLMConnectSriServerItf (ClientData cd, int argc, char *argv[]) {
  NGramLM    *lmP = (NGramLM*) cd;
  int          ac = argc - 1;
  char    *server = NULL;
  int        port = 0;
  int      order  = 0;
  char    *vocabF = NULL;

  if (itfParseArgv(argv[0], &ac, argv+1, 0, 
      "<host>"    , ARGV_STRING, NULL, &server, cd, "host that the server runs on", 
      "<port>"    , ARGV_INT   , NULL, &port  , cd, "port that the server runs on", 
      "<order>"   , ARGV_INT   , NULL, &order , cd, "port that the server runs on", 
      "-vocabFile", ARGV_STRING, NULL, &vocabF, cd, "file to read vocab from",
      NULL) != TCL_OK) return TCL_ERROR;

  return  NGramLMConnectSriServer(lmP, server, port, order, vocabF);
}


/* ========================================================================
    NGramLMItem/ Subs
   ---------------------
    Substitutions section and Items
   ======================================================================== */

/* ------------------------------------------------------------------------
    NGramLMIndex
   ------------------------------------------------------------------------ */

int NGramLMIndex (NGramLM* NGramLM, char* name) 
{
  return listIndex((List*)&(NGramLM->list), name, 0);
}

static LVX NGramLMItemX (LingKS *lksP, char *name)
{
  int i = listIndex((List*)&(lksP->data.ngramLM->list), name, 0);
  return (i == -1) ? LVX_NIL : (LVX) i;
}

static char *NGramLMItemA (LingKS* lksP, int i)
{
  return (i < 0) ? "(null)" : lksP->data.ngramLM->list.itemA[i].name;
}

static int NGramLMItemN (LingKS* lksP)
{
  return lksP->data.ngramLM->list.itemN;
}

static int NGramLMIsDirty (LingKS* lksP)
{
  int dirty = lksP->dirty;
  lksP->dirty = FALSE;
  return dirty;
}

/* ------------------------------------------------------------------------
    NGramLMItemInit/ DeInit
   ------------------------------------------------------------------------ */

static int NGramLMItemInit (NGramLMItem* lmiP, ClientData CD)
{
  assert (lmiP);
  lmiP->name       =  (CD) ? strdup((char*)CD) : NULL;
  return TCL_OK;
}

static int NGramLMItemDeinit( NGramLMItem* lmiP)
{
  if (!lmiP) return TCL_OK;
  if (lmiP->name) { free (lmiP->name); lmiP->name = NULL; }
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMItemConfigureItf
   ------------------------------------------------------------------------ */

static int NGramLMItemConfigureItf (ClientData cd, char *var, char *val)
{
  NGramLMItem* lmiP = (NGramLMItem*)cd;
  NGramLM* lmP = lmiP->lmP;
  int idx, j;
  if (!lmiP) return TCL_ERROR;
  idx = NGramLMIndex (lmiP->lmP, lmiP->name);
  if (!var) {
    ITFCFG(NGramLMItemConfigureItf,cd,"name");
    ITFCFG(NGramLMItemConfigureItf,cd,"linkX");
    return TCL_OK;
  }
  ITFCFG_CharPtr( var,val,"name",  lmiP->name, 1);

  j = (lmP->mgram[0].linkA) ? NJDGetLMLinkIdx (0, idx) : 0;
  ITFCFG_Int(     var,val,"linkX", j,         1);

  ERROR("Unknown option '-%s %s'.\n", var, val ? val : "?");

  return TCL_ERROR;
}


/* ------------------------------------------------------------------------
    NGramLMItemPutsItf
   ------------------------------------------------------------------------ */

static int NGramLMItemPuts (NGramLMItem* NGramLMItem)
{
  itfAppendElement("%s", NGramLMItem->name);
  return TCL_OK;
}

static int NGramLMItemPutsItf( ClientData cd, int argc, char *argv[])
{
  int   ac   =  argc-1;
  NGramLMItem* lmodelItem = (NGramLMItem*)cd;

  if ( itfParseArgv( argv[0], &ac, argv+1, 0, NULL) != TCL_OK)
       return TCL_ERROR;

  return NGramLMItemPuts( lmodelItem);
}


/* ------------------------------------------------------------------------
    NGramLMSubsItf
   ------------------
    return the list of substitutions read from an ARPABO file
   ------------------------------------------------------------------------ */

static ClientData NGramLMSubsAccessItf (ClientData cd, char *name, TypeInfo **ti)
{ 
  return listAccessItf (cd, name, ti);
}

static int NGramLMSubsPuts (NGramLMSubs* item)
{
  itfAppendElement ("%s", item->line);
  return TCL_OK;
}

static int NGramLMSubsPutsItf (ClientData cd, int argc, char *argv[])
{
  int              ac = argc-1;
  NGramLMSubs* item = (NGramLMSubs*) cd;

  if (itfParseArgv (argv[0], &ac, argv+1, 0, NULL) != TCL_OK)
       return TCL_ERROR;

  return NGramLMSubsPuts (item);
}


/* ========================================================================
    NGramLM
   ======================================================================== */

/* ------------------------------------------------------------------------
    Create NGramLM Structure
   ------------------------------------------------------------------------ */

int NGramLMListReInit (NGramLM* lmP)
{
  listDeinit ((List*)&(lmP->list));
  listInit   ((List*)&(lmP->list), itfGetType("NGramLMItem"), 
	      sizeof(NGramLMItem), NGramLMDefault.list.blkSize);
  lmP->list.init    = (ListItemInit  *)NGramLMItemInit;
  lmP->list.deinit  = (ListItemDeinit*)NGramLMItemDeinit;
  return TCL_OK;
}

int NGramLMInit (LingKS* lksP, NGramLM* lmP, char* name)
{
  /* Set the variables in NGramLM */
  lmP->lksP          = lksP;
  lmP->quantize      = 0;
  lmP->order         = -1;
  lmP->history       = -1;
  lmP->mgram         = NULL;
  lmP->segSize       = NGramLMDefault.segSize;
  lmP->log0          = NGramLMDefault.log0;
  lmP->log0Val       = NGramLMDefault.log0Val;
  lmP->remoteChannel = NULL;
  lmP->mmapP         = NULL;
  lmP->mmapS         = 0;

  lmP->lda_obj = NULL;
  lmP->ngram_lda_obj = NULL;

  /* Set the needed pointers in LingKS */
  lksP->lingKSSaveFct     = NGramLMSave;
  lksP->lingKSLoadFct     = NGramLMLoad;
  lksP->lingKSSaveItfFct  = NGramLMSaveItf;
  lksP->lingKSLoadItfFct  = NGramLMLoadItf;
  lksP->lingKSPutsFct     = NGramLMPutsItf;
  lksP->scoreArrayFct     = NGramLMScoreArray;
  lksP->scoreFct          = NGramLMScore;
  /*lksP->scoreFct          = NGramLMScoreSriLMServer;*/
  lksP->itemN             = NGramLMItemN;
  lksP->itemA             = NGramLMItemA;
  lksP->itemX             = NGramLMItemX;
  lksP->isDirty           = NGramLMIsDirty;

  /* Don't use hashed LCTs */
  lmP->hash         = 0;
  NGramLMHashStatus (lmP);

  /* Create the Hash list */
  if (listInit ((List*) &(lmP->lctList), NULL, 
               sizeof (NJDLCT), 1000) != TCL_OK) {
    ERROR ("Couldn't allocate NJDLCT hash list.");
    return TCL_ERROR;
  }
  lmP->lctList.deinit  = NULL;
  lmP->lctList.init    = (ListItemInit  *) njdHashInit;
  lmP->lctList.hashKey = (HashKeyFn     *) njdHashKey;
  lmP->lctList.hashCmp = (HashCmpFn     *) njdHashCmp;

  lmP->lctMem = bmemCreate (16384, 0);

  /* Create the substitutions section */
  if (listInit((List*)&(lmP->subslist), itfGetType("NGramLMSubs"), 
	       sizeof(NGramLMSubs), NGramLMDefault.subslist.blkSize) != TCL_OK) {
    ERROR("Couldn't allocate substitutions list.");
    return TCL_ERROR;
  }

  /* Create the items section */
  if (listInit((List*)&(lmP->list), itfGetType("NGramLMItem"), 
	       sizeof(NGramLMItem), NGramLMDefault.list.blkSize) != TCL_OK) {
    ERROR("Couldn't allocate unigram list.");
    return TCL_ERROR;
  }
  lmP->list.init    = (ListItemInit  *)NGramLMItemInit;
  lmP->list.deinit  = (ListItemDeinit*)NGramLMItemDeinit;

  return TCL_OK;
}


/* ------------------------------------------------------------------------
    Free NGramLM Structure
   ------------------------------------------------------------------------ */

int NGramLMLinkN (NGramLM* lmP)
{
  int useN = listLinkN((List*)&(lmP->list)) - 1;
  if (useN < lmP->lksP->useN) return lmP->lksP->useN;
  else                        return            useN;
}

int NGramLMDeinit (NGramLM *lmP)
{
  int i;

  assert (lmP);

  if (NGramLMLinkN (lmP)) {
    SERROR ("NGramLM '%s' still in use by other objects.\n", lmP->lksP->name);
    return TCL_ERROR;
  } 

  if (lmP->mmapP) {
#ifdef WINDOWS
    WARN ("Not supported under Windows\n");
#else
    munmap (lmP->mmapP, lmP->mmapS);
    lmP->mmapP = NULL;
    lmP->mmapS = 0;

    /* these pointers were not allocated, just set in mmap case */
    for (i = 0; i < lmP->order; i++) {
      MGram* mg = lmP->mgram + i;
      mg->idA       = NULL;
      mg->cprobA    = NULL;
      mg->probA     = NULL;
      mg->cbackoffA = NULL;
      mg->backoffA  = NULL;
      mg->linkA     = NULL;
      mg->segTbl    = NULL;
    }
#endif
  }

  for (i = 0; i < lmP->order; i++)
    NGramLMDeInitMGram (lmP, i);

  return listDeinit ((List*) &(lmP->list));
}


/* ------------------------------------------------------------------------
    NGramLMConfigureItf
   ------------------------------------------------------------------------ */

int NGramLMConfigureItf (ClientData cd, char *var, char *val)
{
  NGramLM* lmodel = (NGramLM*)cd;
  int           old;

  if (!lmodel)
    lmodel = &NGramLMDefault;
  old = lmodel->hash;

  if (!var) {
    ITFCFG(NGramLMConfigureItf,cd,"order");
    ITFCFG(NGramLMConfigureItf,cd,"history");
    ITFCFG(NGramLMConfigureItf,cd,"segSize");
    ITFCFG(NGramLMConfigureItf,cd,"log0");
    ITFCFG(NGramLMConfigureItf,cd,"log0Val");
    ITFCFG(NGramLMConfigureItf,cd,"hashLCT");
    return listConfigureItf((ClientData)&(lmodel->list), var, val);
  }

  ITFCFG_Int(    var,val,"segSize",  lmodel->segSize,          0);
  ITFCFG_Float(  var,val,"log0",     lmodel->log0,             0);
  ITFCFG_Float(  var,val,"log0Val",  lmodel->log0Val,          0);
  ITFCFG_Int(    var,val,"order",    lmodel->order,            1);
  if (streq (var, "history")) {
    if (val) {
      if (atoi(val) >= 0)                             
	lmodel->history = atoi (val);
      if (lmodel->history-1 > (int) sizeof(LCT)/(int) sizeof(LVX)) 
	lmodel->hash    = 1;
      if (old != lmodel->hash)
	NGramLMHashStatus (lmodel);
    }
    itfAppendResult ("%d", lmodel->history);
    return TCL_OK;
  }
  if (streq (var, "hashLCT")) {
    if (val) {
      lmodel->hash = (atoi (val) != 0);
      if (old != lmodel->hash)
	NGramLMHashStatus (lmodel);
    }
    itfAppendResult ("%d", lmodel->hash);
    return TCL_OK;
  }  
  return listConfigureItf((ClientData)&(lmodel->list), var, val);   
}


/* ------------------------------------------------------------------------
    NGramLMAccessItf
   ------------------------------------------------------------------------ */

ClientData NGramLMAccessItf (ClientData cd, char *name, TypeInfo **ti)
{ 
  NGramLM* lmP = (NGramLM*) cd;
  int i, j;

  if (*name == '.') { 
    if (name[1]=='\0') {
       itfAppendElement( "probA(1..%d,0..N)",    lmP->order);
       itfAppendElement( "backOffA(1..%d,0..N)", lmP->order-1);
       itfAppendElement( "idA(2..%d,0..N)",      lmP->order);
       itfAppendElement( "linkA(1..%d,0..N)",    lmP->order-1);
       itfAppendElement( "mgramN(1..%d)",        lmP->order);
       itfAppendElement( "subslist");
       *ti = NULL;
    } else { 

      if (sscanf (name+1, "mgramN(%d)", &i) == 1 && i > 0 && i <= lmP->order) {
	itfAppendElement("%d", lmP->mgram[i-1].itemN);
	*ti = NULL;
	return NULL;
      } else if (sscanf (name+1, "probA(%d,%d)", &i, &j) == 2 &&
		 i > 0 && i <= lmP->order && j >= 0 && j < lmP->mgram[i-1].itemN) {
	MGram *mg = lmP->mgram+i-1;
	if (mg->cprobA)
	  itfAppendElement("%f", UnCompressScore(mg->probA[mg->cprobA[j]]));
        else
	  itfAppendElement("%f", UnCompressScore(mg->probA[j]));
	*ti = NULL;
	return NULL;
      } else if (sscanf (name+1, "backOffA(%d,%d)", &i, &j) == 2 &&
		 i > 0 && i < lmP->order && j >= 0 && j < lmP->mgram[i-1].itemN &&
		 lmP->mgram[i-1].backoffA != NULL) {
	MGram *mg = lmP->mgram+i-1;
	if (mg->cbackoffA)
	  itfAppendElement("%f", UnCompressScore(mg->backoffA[mg->cbackoffA[j]]));
        else
	  itfAppendElement("%f", UnCompressScore(mg->backoffA[j]));
	*ti = NULL;
	return NULL;
      } else if (sscanf (name+1, "idA(%d,%d)", &i, &j) == 2 &&
		 i > 1 && i <= lmP->order && j >= 0 && j < lmP->mgram[i-1].itemN &&
		 lmP->mgram[i-1].idA != NULL) {
	itfAppendElement("%d", lmP->mgram[i-1].idA[j]);
	*ti = NULL;
	return NULL;
      } else if (sscanf (name+1, "linkA(%d,%d)", &i, &j) == 2 &&
		 i > 0 && i < lmP->order && j >= 0 && j < lmP->mgram[i-1].itemN &&
		 lmP->mgram[i-1].linkA != NULL) {
	itfAppendElement("%d %d", NJDGetLMLinkIdx (i-1, j), NJDGetLMLinkIdx (i-1, j+1));
	*ti = NULL;
	return NULL;
      } else if (streq (name+1, "subslist")) {
	*ti = itfGetType ("List");
	return (ClientData) &(lmP->subslist);
      }
    }
  }

  return listAccessItf((ClientData)&(lmP->list), name, ti);
}

static int NGramLMPutsItf (ClientData cd, int argc, char *argv[]) {

  NGramLM* lmP = (NGramLM*) cd;

  return listPutsItf ((ClientData)&(lmP->list),  argc, argv);
}


/* ========================================================================
    Actual score routines
   ======================================================================== */

/* ------------------------------------------------------------------------
    NGramLMFindMGram
   --------------------
    Do a binary search to find an M-Gram in the list of M-Grams <w1,w2,...>
    It returns the level of the M-Gram found, searchX contains the item index
   ------------------------------------------------------------------------ */

int NGramLMFindMGram (NGramLM* lmP, int m, LVX *arr, int *searchX)
{
  int i, j;

  /* Init search */
  *searchX = (int) arr[0];

  /* Descend levels until we find the item*/
  for (i = 1; i < m; i++) {    
    /* Does this M-Gram exist? Binary search ...
       (faster than 'bsearch') */
    int a = NJDGetLMLinkIdx (i-1, *searchX);
    int o = NJDGetLMLinkIdx (i-1, *searchX+1) - 1;    

    while (a+4 < o) {
      if (lmP->mgram[i].idA[(j = (a+o) >> 1)] > arr[i]) o = j-1;
      else                                              a = j;
    }
    
    /* Now linear search ... */
    for (j = a; j < o && lmP->mgram[i].idA[j] != arr[i]; j++);
    
    if (a <= o && lmP->mgram[i].idA[j] == arr[i]) /* Yes! Found! */
      *searchX = j;
    else { /* No! Not found. */
      if (i == 1)
	*searchX = (int) arr[0];
      return i;
    }
  }

  return m;
}


/* ------------------------------------------------------------------------
    NGramLMScore
   ---------------- 
    Compute the score of the N-Gram language model for 'w' given 'lct'.
   ------------------------------------------------------------------------ */

lmScore NGramLMScore (LingKS* lksP, LCT lct, LVX w, int usehistory)
{
  NGramLM*  lmP = lksP->data.ngramLM;
  lmScore    prob = 0;
  LVX*          l = lvxBuffer;
  int               searchX, nX, n;
  MGram*            ng;
  //int i           = -1;

  //char          *ngram = NULL;
  //Tcl_DString *dstrPtr = malloc(sizeof(*dstrPtr));  


  /* Get 'n' words in 'lvxBuffer', for a 3-Gram LM,
     n == 2 and l[0..1] == 'the history' */
  n    = (usehistory) ? lmP->history : lmP->order-1;
  lksP->decodeLCT (lksP, lct, lvxBuffer, n);
  l[n] = (LVX) w;

  /* Build a string of the ngram in buffer l */
  /*
  Tcl_DStringInit(dstrPtr);
  Tcl_DStringAppend(dstrPtr, lksP->itemA(lksP,l[0]), -1);
  for (i=0; i<=n; i++) {
    Tcl_DStringAppend(dstrPtr, " ", -1);
    Tcl_DStringAppend(dstrPtr, lksP->itemA(lksP,l[i]), -1);
  }
  Tcl_DStringAppend(dstrPtr, "\n", -1);
  ngram = Tcl_DStringValue(dstrPtr);
  */

  /* Loop */
  while ((nX = NGramLMFindMGram (lmP, n+1, l, &searchX)) <= n) {
    ng = lmP->mgram + nX - 1;
    if (nX == n)
      prob += (ng->cbackoffA) ? ng->backoffA[ng->cbackoffA[searchX]] :
	                        ng->backoffA[searchX];
    l++, n--;
  }
  ng    = lmP->mgram + nX - 1;
  prob += (ng->cprobA) ? ng->probA[ng->cprobA[searchX]] :
                         ng->probA[searchX];

  /*  INFO("Calculated prob %f for %s", prob, ngram);*/

  /* Free allocated memory */
  //Tcl_DStringFree(dstrPtr);
  //free(dstrPtr);

  return prob;
}


/* ------------------------------------------------------------------------
    Bigrams
   ---------
    Fills an array with bigram scores + a given offset
   ------------------------------------------------------------------------ */

static int Bigrams (NGramLM *lmP, LVX *l, lmScore *arr, lmScore Boffset)
{
  int                       a, o, i, n;
  unsigned char*                   BgL;
  lmScore          Uoffset, *BgS, *UgS;
  MGram*          ug = lmP->mgram;
  MGram*          bg = lmP->mgram+1;
  LVX           *idA = bg->idA;

  n       = lmP->list.itemN;
  a       = NJDGetLMLinkIdx (0, l[0]);
  o       = NJDGetLMLinkIdx (0, l[0]+1);
  Uoffset = (ug->cbackoffA) ? ug->backoffA[ug->cbackoffA[*l]] + Boffset :
                              ug->backoffA[*l]                + Boffset;
  BgS     = bg->probA;
  UgS     = ug->probA;
  BgL     = bg->cprobA;

  if (ug->cprobA)
    FATAL ("Please don't compress Unigram scores.\n");
  else {

    if (BgL) { /* Compressed Bigram-scores */
      for (i = 0; a < o; a++) {
	while (i < idA[a])
	  arr[i] = Uoffset + UgS[i],      i++;
	arr[i]   = Boffset + BgS[BgL[a]], i++;
      }
      
    } else {   /* Un-compressed Bigram-scores */
      for (i = 0; a < o; a++) {
	while (i < idA[a])
	  arr[i] = Uoffset + UgS[i], i++;
	arr[i]   = Boffset + BgS[a], i++;
      }

    }

    /* Do remaining unigram backoffs */
    while (i < n) {
      arr[i]   = Uoffset + UgS[i];
      i++;
    } 
  }  

  return TCL_OK;
}
  
  
/* ------------------------------------------------------------------------
    PartFill
   ----------
    Does the dirty work for ScoreArrays. 
   ------------------------------------------------------------------------ */

static int PartFill (NGramLM *lmP, LVX *l, lmScore *arr, lmScore offset, int m)
{
  MGram*          mg = lmP->mgram+m;
  lmScore       *pbA = mg->probA;
  unsigned char *cpA = mg->cprobA;
  lmScore       off2 = offset;
  int                  i, nX;

  if ((nX = NGramLMFindMGram (lmP, m, l, &i)) == m) {
    MGram* ng = lmP->mgram+nX-1;
    off2 += (ng->cbackoffA) ? ng->backoffA[ng->cbackoffA[i]] :
                              ng->backoffA[i];
  }

  /* -----------
      Recursion
     ----------- */
  if (m == 2) Bigrams  (lmP, l+1, arr, off2);
  else        PartFill (lmP, l+1, arr, off2, m-1);

    /* -----------------------------------
        Overwrite the few remaining items
       ----------------------------------- */
  if (nX == m) {
    int    a = NJDGetLMLinkIdx (m-1, i);
    int    o = NJDGetLMLinkIdx (m-1, i+1);
    LVX *idA = mg->idA;

    if (cpA) /* Compressed case */
      while (a < o) {
	arr[idA[a]] = offset + pbA[cpA[a]];
	a++;
      }
    else /* No compression */
      while (a < o) {
	arr[idA[a]] = offset + pbA[a];
	a++;
      }
  }
  
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMScoreArray
   ---------------------
    Fills a whole array with scores, doesn't care much about other things
    Called by the search, it therefore uses LCT
   ------------------------------------------------------------------------ */

int NGramLMScoreArray (LingKS *lksP, LCT lct, lmScore *arr, int usehistory)
{
  NGramLM* lmP = lksP->data.ngramLM;
  LVX*         l = lvxBuffer;  
  int          n = (usehistory) ? lmP->history : lmP->order-1;

  lksP->decodeLCT (lksP, lct, l, n);

  switch (n) {
  case 0: /* ---------------------------------------------
	      Unigrams: just copy the probabilities array
	     --------------------------------------------- */
    memcpy (arr, lmP->mgram[0].probA, lmP->list.itemN*sizeof (lmScore));
    break;

  case 1: /* --------------------------------
              Bigrams or backoff to unigrams
	     -------------------------------- */
    Bigrams (lmP, l, arr, 0);
    break;

  default: /* -------------------
	       Long-range models
              ------------------- */
    PartFill (lmP, l, arr, 0, n);
    break;

  }

  // perform marginal adaptation on the cache table
#ifdef CMUJRTK
  if (lmP->lda_obj) {
    INFO ("Adapting ...\n");
    //Marginal_Adapt_Cache(lmP->lda_obj, arr);
  }
#endif
  return TCL_OK;
}


/* ------------------------------------------------------------------------
    NGramLMScoreSriLMServer
   ------------------------
    Compute the score of the N-Gram language model for 'w' given 'lct'.
   ------------------------------------------------------------------------ */
lmScore NGramLMScoreSriLMServer(LingKS* lksP, LCT lct, LVX w, int usehistory) {
  NGramLM*         lmP = lksP->data.ngramLM;
  double          prob = 0;
  LVX*               l = lvxBuffer;
  int                n = -1;
  int                i;
  Tcl_Channel  channel = lksP->data.ngramLM->remoteChannel;
  int            cRead = 0;
  int             cidx;
  /*  int           ngsize = 0; */

  /* reset the SRIstrObj to "" */
  Tcl_SetStringObj( SRIstrObjPtr, 0, 0 );

  /* Get 'n' words in 'lvxBuffer', for a 3-Gram LM,
  n == 2 and l[0..1] == 'the history' */
  n    = (usehistory) ? lmP->history : lmP->order-1;
  lksP->decodeLCT (lksP, lct, lvxBuffer, n);
  l[n] = (LVX) w;

   /* Build a string of the ngram in buffer l */
  Tcl_DStringInit(SRIdstrPtr);
  Tcl_DStringAppend(SRIdstrPtr, lksP->itemA(lksP,l[0]), -1);
  for (i=1; i<=n; i++) {
    Tcl_DStringAppend(SRIdstrPtr, " ", -1);
    Tcl_DStringAppend(SRIdstrPtr, lksP->itemA(lksP,l[i]), -1);
  }
  Tcl_DStringAppend(SRIdstrPtr, "\n", -1);
  currNGSP.ngram = Tcl_DStringValue(SRIdstrPtr);

  /*INFO("Got String %s\n", currNGSP.ngram);*/

  /* building local NGSP */
  currNGSP.prob  = 0.0;

  /* check whether this specific ngram-prob was allready retrieved an put into the cachelist */ 
  if ( ( cidx = listIndex( (List*) &(lmP->ngspCL), &currNGSP, 0 ) ) == -1)  {
    sri_cache_miss++;

    /* Write the ngram string out to the SRI LM server; flush the channel */
    Tcl_WriteChars(channel, currNGSP.ngram, -1);
    Tcl_Flush(channel);
    /*INFO("Wrote the string\n");*/
  
    /* Read the result from the SRI LM server */
    Tcl_GetsObj(channel, SRIstrObjPtr);
    /*INFO("SRI LM Server answered: %s\n", Tcl_GetString(SRIstrObjPtr));*/

    /* Convert to double and return the value */
    if (Tcl_GetDoubleFromObj(itf, SRIstrObjPtr, &prob) != TCL_OK) {
      ERROR("Could not convert result %s to double.\n", Tcl_GetString(SRIstrObjPtr));
      return LMSCORE_MAX;
    }
    /*INFO("Extracted probability from objected: %f\n", prob);*/

    /* Remove garbage on the channel */
    Tcl_SetChannelOption(itf, channel, "-blocking", "FALSE");
    cRead = Tcl_ReadChars(channel, SRIstrObjPtr, -1, 0);
    /* INFO("SRI LM Server read %d chars: '%s'\n", cRead, strObjPtr ); */
    Tcl_SetChannelOption(itf, channel, "-blocking", "TRUE");

    /*INFO("Calculated prob %f for %s", prob, currNGSP.ngram);*/
    currNGSP.prob = prob;

    /*INFO("inserting ngsp: ngram = %s, prob = %f\n", currNGSP.ngram, currNGSP.prob );*/
    /*listNewItem( (NGramLMNGSPCacheList*) &(lmP->ngspCL), &currNGSP );*/
    ngspCLNewItem( (List* ) &(lmP->ngspCL), &currNGSP );

    return (lmScore) prob;

  } else {
    sri_cache_hit++;
    /*INFO( "got prob from cachelist\n");*/

    return (lmScore) lmP->ngspCL.itemA[cidx % lmP->ngspCL.itemMax].prob;

  }  

}

/* ------------------------------------------------------------------------
    NGramLMScoreArraySriLMServer
   ------------------------------
    Fills a whole array with scores, doesn't care much about other things
    Called by the search, it therefore uses LCT
   ------------------------------------------------------------------------ */
int NGramLMScoreArraySriLMServer (LingKS *lksP, LCT lct, lmScore *arr, int usehistory) {
	NGramLM*   lmP = lksP->data.ngramLM;
	/*  LVX*         l = lvxBuffer;
      int          n = (usehistory) ? lmP->history : lmP->order-1; */
	LVX          i = LVX_NIL;
	int       cidx;

	currLCTAP.lct = lct;

	if ( ( cidx = listIndex( (List*) &(lmP->lctapCL), &currLCTAP, 0 ) ) == -1)  {
		lcta_cache_miss++;

		/* Loop over all words in the LM */
		for(i = 0; i < lmP->list.itemN; i++) {
			arr[i] = NGramLMScoreSriLMServer(lmP->lksP, lct, (LVX) i, usehistory);
		}
		currLCTAP.arr = arr;
		currLCTAP.itemN = lmP->list.itemN;

		/*listNewItem( (NGramLMLCTAPCacheList*) &(lmP->lctapCL), &currLCTAP);*/
		lctapCLNewItem((List*) &(lmP->lctapCL), &currLCTAP);
	}
	else {
		lcta_cache_hit++;

		cidx = cidx % lmP->lctapCL.itemMax;

		/* MEMCPY */
		/*    for(i = 0; i < lmP->lctapCL.itemA[ cidx ].itemN; i++) {
      arr[i] = lmP->lctapCL.itemA[cidx].arr[i];
      }*/
		memcpy( arr, lmP->lctapCL.itemA[cidx].arr, lmP->lctapCL.itemA[cidx].itemN*sizeof(lmScore));


	}
	return TCL_OK;
}


/* ========================================================================
    Type Information
   ======================================================================== */

static Method NGramLMItemMethod[] = { 
  { "puts", NGramLMItemPutsItf, NULL },
  {  NULL, NULL, NULL } 
};

TypeInfo NGramLMItemInfo = { 
  "NGramLMItem", 0, -1, NGramLMItemMethod, 
  NULL, NULL,
  NGramLMItemConfigureItf, NULL,
  itfTypeCntlDefaultNoLink, 
  "N-gram Language Model Item\n" 
};

static Method NGramLMSubsMethod[] = { 
  { "puts", NGramLMSubsPutsItf, NULL },
  {  NULL, NULL, NULL } 
};

TypeInfo NGramLMSubsInfo = { 
  "NGramLMSubs", 0, -1, NGramLMSubsMethod, 
  NULL, NULL,
  NULL, NGramLMSubsAccessItf,
  itfTypeCntlDefaultNoLink, 
  "N-gram Language Model Substitution Item\n" 
};

static Method NGramLMMethod[] = { 
  { "puts"               , NGramLMPutsItf               , NULL },
  { "connectSriServer"   , NGramLMConnectSriServerItf   , "Connect to a running SRI LM Server" },
  { "disconnectSriServer", NGramLMDisconnectSriServerItf, "disconnect from the SRI LM Server" },
  { "readVocab"          , NGramLMReadVocabItf          , "fill NGram item list from vocab file, e.g. for SRI LM usage" },
  {  NULL                , NULL                         , NULL } 
};

TypeInfo NGramLMInfo = {
  "NGramLM", 0, -1,    NGramLMMethod, 
  NULL,                  NULL,
  NGramLMConfigureItf, NGramLMAccessItf, NULL,
  "N-gram Language Model\n" 
};


int NGramLM_Init()
{
  if (!NGramLMInitialized) {
    NGramLMDefault.list.itemN       = 0;
    NGramLMDefault.list.blkSize     = 1000;
    NGramLMDefault.subslist.itemN   = 0;
    NGramLMDefault.subslist.blkSize = 100;
    NGramLMDefault.segSize          = 12;
    NGramLMDefault.log0             = -99.0;
    NGramLMDefault.log0Val          =  -5.0;

    itfNewType (&NGramLMItemInfo);
    itfNewType (&NGramLMSubsInfo);
    itfNewType (&NGramLMInfo);

    NGramLMInitialized = TRUE;
  }
  return TCL_OK;
}