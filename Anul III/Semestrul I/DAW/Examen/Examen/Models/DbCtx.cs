using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Examen.Models
{
    public class DbCtx : DbContext
    {
        public DbCtx() : base("PoezieCS")
        {
            System.Data.Entity.Database.SetInitializer<DbCtx>(new Initp());
        }

        public DbSet<Poezie> Poezii { get; set; }
        public DbSet<Volum> Volume { get; set; }
    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    {
        protected override void Seed(DbCtx context)
        {
            context.Volume.Add(new Volum
            {
                Denumire = "Volum1",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Autor1",
                        Titlu = "Titlu1",
                        NrStrofe = 10
                    },
                    new Poezie
                    {
                        Autor = "Autor2",
                        Titlu = "Titlu2",
                        NrStrofe = 3
                    }
                }
            });

            context.Volume.Add(new Volum
            {
                Denumire = "Volum2",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Autor3",
                        Titlu = "Titlu3",
                        NrStrofe = 4
                    },
                    new Poezie
                    {
                        Autor = "Autor4",
                        Titlu = "Titlu4",
                        NrStrofe = 3
                    }
                    
                }
            });

            context.Volume.Add(new Volum
            {
                Denumire = "Volum3",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Autor5",
                        Titlu = "Titlu5",
                        NrStrofe = 2
                    },
                    new Poezie
                    {
                        Autor = "Autor6",
                        Titlu = "Titlu6",
                        NrStrofe = 23
                    }
                }
            });
            context.SaveChanges();
            base.Seed(context);
        }
    }
}