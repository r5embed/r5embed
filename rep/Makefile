#	Makefile
#	2020-01-30	Markku-Juhani O. Saarinen <mjos@pqshield.com>
#	Copyright (c) 2020, PQShield Ltd. All rights reserved.

PROJ		= rep
TEXSRC		= $(PROJ).tex

$(PROJ).pdf:	$(TEXSRC)
	pdflatex $(PROJ)
	pdflatex $(PROJ)

clean:
	rm -f	*.aux *.dvi *.bbl *.blg *.log *.toc *.lof \
			*.thm *.out $(PROJ).pdf
