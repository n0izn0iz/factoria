#ifndef ENERGY_H
#define ENERGY_H

#define NRG_BATMAXLVL 10000

typedef struct		s_battery
{
	int					level;
	int					x;
	int					y;
	struct s_battery*	next;
}					t_battery;

typedef struct		s_generator
{
	unsigned int		speed;
	int					x;
	int					y;
	struct s_generator*	next;
}					t_generator;

typedef struct		s_consumer
{
	int					buffer;
	int					x;
	int					y;
	struct s_consumer*	next;
}					t_consumer;

typedef struct		s_nrgnetwork
{
	t_battery*				batteries;
	t_generator*			generators;
	t_consumer*				consumers;
	struct s_nrgnetwork*	next;
	int						balance;
	int						capacity;
	int						maxcap;
}					t_nrgnetwork;

void		nrg_addbattery(t_battery** bat, int x, int y);
void		nrg_addgenerator(t_generator** gen, int x, int y);
void		nrg_addconsumer(t_consumer** csm, int x, int y, int firstcons);
void		nrg_addnetwork(t_nrgnetwork** net, t_battery* bat, t_generator* gen, t_consumer* csm);
void		nrg_updatenetwork(t_nrgnetwork** net);
void		nrg_printnetwork(t_nrgnetwork* net);

#endif
