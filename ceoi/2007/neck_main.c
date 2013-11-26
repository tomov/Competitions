#include <stdio.h>
#include <string.h>
#include "necklace.h"

static void interactive (void)
{
  char buf[1000];
  char cmd[1000];
  int id, param, last = 0;
  char op;
  int left;

  init ();
  printf ("Initiated\n");

  while (1)
    {
      if (!fgets (buf, 1000, stdin))
        return;

      if (sscanf (buf, "%s %d %c %d %d", cmd, &id, &op, &left, &param) == 5
	  && !strcmp (cmd, "create"))
	{
	  if (op != 'A' && op != 'R')
	    printf("'%c' is an invalid operation for create.\n", op);
	  else if (id > last)
	    printf("Necklace %d was not created yet.\n", id);
	  else
	    {
	      create (id, op, left, param);
	      last++;
	      printf ("Done\n");
	    }
	}
      else if (sscanf (buf, "%s %d %d", cmd, &id, &left) == 3
	       && !strcmp (cmd, "pearl"))
	{
	  if (id > last)
	    printf("Necklace %d was not created yet.\n", id);
	  else
	    printf ("Returns %d\n", pearl (id, left));
	}
      else if (sscanf (buf, "%s", cmd) == 1
	       && !strcmp (cmd, "quit"))
	return;
      else
	printf("Invalid command.\n");
    }
}

static void fixed (void)
{
  int x;

  init ();
  create (0, 'A', 1, 5);
  create (1, 'A', 1, 3);
  if ((x = pearl (2, 0)) != 5)
    {
      printf("Expected answer to pearl (2, 0) is 5, not %d\n", x);
      return;
    }
  create (2, 'R', 0, 0);
  if ((x = pearl (3, 0)) != 3)
    {
      printf("Expected answer to pearl (3, 0) is 3, not %d\n", x);
      return;
    }
  if ((x = pearl (2, 0)) != 5)
    {
      printf("Expected answer to pearl (2, 0) is 5, not %d\n", x);
      return;
    }

  printf("OK\n");
}

int main(int argc, char **argv)
{
  if (argc == 2)
    interactive ();
  else
    fixed ();
  return 0;
}
