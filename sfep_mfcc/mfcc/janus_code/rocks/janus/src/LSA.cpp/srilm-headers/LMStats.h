/*
 * LMStats.h --
 *	Generic LM statistics interface
 *
 * Copyright (c) 1995-2009 SRI International.  All Rights Reserved.
 *
 * @(#)$Header: /home/srilm/devel/lm/src/RCS/LMStats.h,v 1.9 2009/06/11 05:08:30 stolcke Exp $
 *
 */

#ifndef _LMStats_h_
#define _LMStats_h_

#include <stdio.h>

#include "Boolean.h"
#include "Vocab.h"
#include "Debug.h"
#include "LM.h"

class LMStats: public Debug
{
public:
    LMStats(Vocab &vocab);
    virtual ~LMStats();

    virtual unsigned int countSentence(const VocabString *words) = 0;
    virtual unsigned int countSentence(const VocabString *words,
							const char *weight) = 0;
    virtual unsigned int countSentence(const VocabIndex *words) = 0;

    virtual unsigned int countString(char *sentence, Boolean weighted = false);
    virtual unsigned int countFile(File &file, Boolean weighted = false);

    virtual Boolean read(File &file) = 0;
    virtual void write(File &file) = 0;

    virtual void memStats(MemStats &stats) = 0;
					/* compute memory stats */
    Vocab &vocab;			/* vocabulary */
    Boolean openVocab;			/* whether to add words as needed */

    Boolean addSentStart;		/* add <s> tags in counting */
    Boolean addSentEnd;			/* add </s> tags in counting */

    TextStats stats;			/* training data stats */
};

#endif /* _LMStats_h_ */
