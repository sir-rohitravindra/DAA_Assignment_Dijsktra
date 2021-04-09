
        int dst,wt;
        while(fgetc(fp)!='\n' && !feof(fp))
        {                            
            //fseek(fp,-1,SEEK_CUR);
            fscanf(fp,"%d %d",&dst,&wt);
            printf("\t%d,%d",dst,wt);
        }
        printf("\n");
        
        
    }
    
}

/*
*/