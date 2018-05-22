//____________________________________________________RESOLUCIÓN DE PROBLEMAS[SUBRUTINAS]________________________________________________

int calcChoice(int fila, int colum)
{
    int wallCount = matriz[fila][colum];
    int option_Count = 0;
    //printf("\nWall COunt = %d\n", wallCount);
    if( wallCount >= 8 )
    {
        opciones[option_Count] = 8;
        option_Count++;
        wallCount -=8;
    }
    if(wallCount >= 4 )
    {
        opciones[option_Count] = 4;
        option_Count++;
        wallCount -=4;
    }
    if(wallCount >= 2)
    {
        opciones[option_Count] = 2;
        option_Count++;
        wallCount -=2;
    }
    if(wallCount >= 1 )
    {
        opciones[option_Count] = 1;
        option_Count++;
        wallCount -=1;
    }
    return option_Count;

}

void random_chose( )
{
    int fila = RATA[0];
    int colum = RATA[1];
    //printf("IN ramdom, [%d][%d]\n", fila, colum);
    int opciones_size = calcChoice(fila, colum);
    int option = opciones[ rand()%opciones_size ];
    pRATA[0]=RATA[0];
    pRATA[1]= RATA[1];
    if( option == 1 )
    {
        RATA[1]++;
    //    printf("Derecha\n");
    }
    else if( option == 2 )
    {
        RATA[0]++;
  //      printf("Abajo\n");
    }
    else if( option == 4 )
    {
        RATA[1]--;
//        printf("Izquierda\n");
    }
    else if( option == 8 )
    {
        RATA[0]--;
//        printf("Arriba\n");
    }
}

int hasFront(int direction)
{
    int wallCount = matriz[ RATA[0] ][ RATA[1] ];
    if(wallCount >=8)
    {
        if(direction==90) return 1;
        else wallCount -=8;
    }
    if(wallCount >=4)
    {
        if(direction==180) return 1;
        else wallCount -=4;
    }
    if(wallCount >=2)
    {
        if(direction==270) return 1;
        else wallCount -=2;
    }
    if(wallCount >=1)
    {
        if(direction==0) return 1;
        else wallCount -=1;
    }
    return 0;
}

int hasRigth(int direction)
{
    int wallCount = matriz[ RATA[0] ][ RATA[1] ];
    // printf("\nHas_rigth_wall count = %d", wallCount);
    if(wallCount >=8)
    {
        if(direction==180) return 0;
        else wallCount -=8;
    }
    if(wallCount >=4)
    {
        if(direction==270) return 0;
        else wallCount -=4;
    }
    if(wallCount >=2)
    {
        if(direction==0) return 0;
        else wallCount -=2;
    }
    if(wallCount >=1)
    {
        if(direction==90) return 0;
        else wallCount -=1;
    }
    return 1;
}

int hasLeft(int direction)
{
    int wallCount = matriz[ RATA[0] ][ RATA[1] ];
    if(wallCount >=8)
    {
        if(direction==0) return 0;
        else wallCount -=8;
    }
    if(wallCount >=4)
    {
        if(direction==90) return 0;
        else wallCount -=4;
    }
    if(wallCount >=2)
    {
        if(direction==180) return 0;
        else wallCount -=2;
    }
    if(wallCount >=1)
    {
        if(direction==270) return 0;
        else wallCount -=1;
    }
    return 1;
}

int adelante(int direction)
{
    pRATA[0] = RATA[0];
    pRATA[1] = RATA[1];
    if(direction==0) RATA[1]++;
    else if(direction==90) RATA[0]--;
    else if(direction==180) RATA[1]--;
    else if(direction=270) RATA[0]++;
}

void myPause () {
  printf ( "Press [Enter] to continue ...\t" );
  fflush ( stdout );
  getchar();
}


//_________________________________________________SOLUCIONES PRINCIPALES_____________________________________________-
void randomMouse()
{
    RATA[0] = Entry[0];
    RATA[1] = Entry[1];
    if( !hasBegun )
    {
        matriz[ Entry[0] ][ Entry[1] ] -=4;
        matriz[ Exit[0] ][ Exit[1] ] -=1;
        hasBegun++;
    }
    int cant_nodos = 1;
    //printf("\nEntrada [%d][%d]\nSalida [%d][%d]\n",Entry[0], Entry[1], Exit[0], Exit[1]);

    while( RATA[0] != Exit[0] || RATA[1] != Exit[1] )
    {
        printf("\nCurrent [%d][%d]\n", RATA[0], RATA[1]);
        random_chose();
        cant_nodos++;
    }
    //printf("Salimos --> Current [%d][%d]\n", RATA[0], RATA[1]);
    printf("Cant Nodos = %d\n", cant_nodos);
}

void rigth_hand()
{
    if( !hasBegun )
    {
        matriz[ Entry[0] ][ Entry[1] ] -=4;
        matriz[ Exit[0] ][ Exit[1] ] -=1;
        hasBegun++;
    }
    RATA[0] = Entry[0];
    RATA[1] = Entry[1];
    int cant_nodos=1;
    int front_D=0;
    int rigth_D=270;
    while( RATA[0] != Exit[0] || RATA[1] != Exit[1] )
    {
        if( hasRigth(front_D) )
        {
            if( hasFront(front_D) )
            {
                adelante(front_D);
                cant_nodos++;
            }
            else
            {
                rigth_D = front_D;
                front_D = (rigth_D+90)%360;
            }
        }
        else
        {
            front_D = rigth_D;
            rigth_D = (front_D+270)%360;
            adelante(front_D);
            cant_nodos++;
        }
    }
    printf("\nCant Nodo = %d\n", cant_nodos);
}

void left_hand()
{
    if( !hasBegun )
    {
        matriz[ Entry[0] ][ Entry[1] ] -=4;
        matriz[ Exit[0] ][ Exit[1] ] -=1;
        hasBegun++;
    }
    RATA[0] = Entry[0];
    RATA[1] = Entry[1];
    int cant_nodos=1;
    int front_D=0;
    int left_D=90;
    while( RATA[0] != Exit[0] || RATA[1] != Exit[1] )
    {
        /*int wallCount = matriz[ RATA[0] ][ RATA[1] ];
        printf("\n%d) ", cant_nodos);
        printf("\ncurrent = [%d][%d]",RATA[0], RATA[1]);
        printf("\nDirection = %d",front_D);
        printf("\nWallCount = %d", wallCount);
        printf("\n");
        myPause();*/
        if( hasLeft(front_D) )
        {
            if( hasFront(front_D) )
            {
                adelante(front_D);
                cant_nodos++;
            }
            else
            {
                left_D = front_D;
                front_D = (left_D+270)%360;
            }
        }
        else
        {
            front_D = left_D;
            left_D = (front_D+90)%360;
            adelante(front_D);
            cant_nodos++;
        }
    }
    printf("\nCant Nodo = %d\n", cant_nodos);
}


void rigth_hand_feo()
{
    if( !hasBegun )
    {
        matriz[ Entry[0] ][ Entry[1] ] -=4;
        matriz[ Exit[0] ][ Exit[1] ] -=1;
        hasBegun++;
    }
    RATA[0] = Entry[0];
    RATA[1] = Entry[1];
    int cant_nodos=1;
    int front_D=0;
    int rigth_D=270;
    while( RATA[0] != Exit[0] || RATA[1] != Exit[1] )
    {
        int wallCount = matriz[ RATA[0] ][ RATA[1] ];
        printf("\n%d) ", cant_nodos);
        printf("\ncurrent = [%d][%d]",RATA[0], RATA[1]);
        printf("\nDirection = %d",front_D);
        printf("\nWallCount = %d", wallCount);
        printf("\n");
        myPause();
        if( hasFront(front_D) )
        {
            adelante(front_D);
            cant_nodos++;
        }
        else
        {
            front_D = rigth_D;
            rigth_D = (rigth_D+90)%360;
        }
    }
    printf("\nCant Nodo = %d\n", cant_nodos);
}
