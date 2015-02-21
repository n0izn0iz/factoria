#ifndef TREERENDERER_H
# define TREERENDERER_H

# include <stdbool.h>
# include "qtree/qtree.h"
# include "misc/sdlhandler.h"
# include "misc/point.h"

void	drawtree(t_sdlh* sdlh, const t_qtree* tree, t_fpoint* campos, t_ipoint* winoff, double zoom, bool drawgrid);

#endif
