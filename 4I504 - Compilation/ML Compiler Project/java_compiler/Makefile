#
# MASTER STL M1 - Cours CA - 2005/2006
# 
# Makefile du typeur, de l'evaluateur et du compialteur d'un mini-ML
#

CAMLC=ocamlc
CAMLLINK=$(CAMLC) -o 
CAMLLEX=ocamllex
CAMLYACC=ocamlyacc
CAMLDEP=ocamldep
NAME=java

CIBLES=intertypeur intereval ml2$(NAME)

SRCS =  util.ml types.ml  alex.ml asyn.ml  typeur.ml env_typeur.ml intertypeur.ml eval.ml env_eval.ml intereval.ml env_trans.ml lift.ml langinter.ml trans.ml prod.ml comp.ml 

IOBJS =  util.cmo types.cmo
SOBJS = alex.cmo  asyn.cmo  typeur.cmo env_typeur.cmo 

TOBJS = $(IOBJS) $(SOBJS)
EOBJS = $(TOBJS) eval.cmo env_eval.cmo 

COBJS = env_trans.cmo lift.cmo langinter.cmo trans.cmo prod.cmo comp.cmo 
cible: $(CIBLES)

intertypeur: $(IOBJS) alex.ml asyn.ml  asyn.cmi $(TOBJS)
	$(CAMLLINK) $@ $(TOBJS) intertypeur.ml

intereval: $(IOBJS) alex.ml asyn.ml alex.cmi asyn.cmi $(TOBJS) env_eval.cmo
	$(CAMLLINK) $@ $(EOBJS) intereval.ml

ml2$(NAME): $(IOBJS) alex.ml asyn.ml alex.cmi asyn.cmi $(TOBJS) $(COBJS)
	$(CAMLLINK) $@ $(EOBJS)  $(COBJS) maincomp.ml

java: prodjava.ml
	rm prod.ml
	ln -s prodjava.ml prod.ml

distrib:
	tar -cvf distrib.tar $(SRCS) alex.mll  asyn.mly asyn.mli Makefile alex.mll alex.mli asyn.mly asyn.mli prodjava.ml maincomp.ml runtime.java Makefile


.SUFFIXES:

.SUFFIXES: .mll .mly .ml .mli .cmo .cmi 

.ml.cmo:
	$(CAMLC) -c $<

.mli.cmi:
	$(CAMLC) -c $<

.mly.ml:
	$(CAMLYACC) $<

.mll.ml:
	$(CAMLLEX) $<

clean:
	/bin/rm -f *~ *.cmi *.cmo alex.ml asyn.ml $(CIBLE)


depend:
	cp Makefile Makefile.bak
	(sed -e '/^#.*DEPEND.*automatic/,$$d' Makefile.bak; \
	echo '### DEPENDENCIES: automatically generated. Do not edit'; \
	$(CAMLDEP) $(SRCS)) > Makefile

### DEPENDENCIES: automatically generated. Do not edit
alex.cmo: asyn.cmi util.cmo 
alex.cmx: asyn.cmx util.cmx 
asyn.cmo: types.cmo util.cmo asyn.cmi 
asyn.cmx: types.cmx util.cmx asyn.cmi 
typeur.cmo: types.cmo util.cmo 
typeur.cmx: types.cmx util.cmx 
env_typeur.cmo: alex.cmo asyn.cmi types.cmo typeur.cmo util.cmo 
env_typeur.cmx: alex.cmx asyn.cmx types.cmx typeur.cmx util.cmx 
intertypeur.cmo: alex.cmo asyn.cmi env_typeur.cmo types.cmo typeur.cmo \
    util.cmo 
intertypeur.cmx: alex.cmx asyn.cmx env_typeur.cmx types.cmx typeur.cmx \
    util.cmx 
eval.cmo: types.cmo 
eval.cmx: types.cmx 
env_eval.cmo: env_typeur.cmo eval.cmo types.cmo typeur.cmo 
env_eval.cmx: env_typeur.cmx eval.cmx types.cmx typeur.cmx 
intereval.cmo: alex.cmo asyn.cmi env_eval.cmo env_typeur.cmo eval.cmo \
    intertypeur.cmo types.cmo typeur.cmo 
intereval.cmx: alex.cmx asyn.cmx env_eval.cmx env_typeur.cmx eval.cmx \
    intertypeur.cmx types.cmx typeur.cmx 
env_trans.cmo: types.cmo 
env_trans.cmx: types.cmx 
lift.cmo: env_trans.cmo types.cmo typeur.cmo 
lift.cmx: env_trans.cmx types.cmx typeur.cmx 
langinter.cmo: types.cmo 
langinter.cmx: types.cmx 
trans.cmo: env_trans.cmo langinter.cmo types.cmo typeur.cmo util.cmo 
trans.cmx: env_trans.cmx langinter.cmx types.cmx typeur.cmx util.cmx 
prod.cmo: env_trans.cmo env_typeur.cmo langinter.cmo types.cmo typeur.cmo 
prod.cmx: env_trans.cmx env_typeur.cmx langinter.cmx types.cmx typeur.cmx 
comp.cmo: alex.cmo asyn.cmi env_trans.cmo env_typeur.cmo intertypeur.cmo \
    lift.cmo prod.cmo trans.cmo types.cmo typeur.cmo 
comp.cmx: alex.cmx asyn.cmx env_trans.cmx env_typeur.cmx intertypeur.cmx \
    lift.cmx prod.cmx trans.cmx types.cmx typeur.cmx 
