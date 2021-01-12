using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Sport.Models
{
    public class DbCtx : DbContext
    {
        public DbCtx() : base("SportCS")
        {
            System.Data.Entity.Database.SetInitializer<DbCtx>(new Initp());
        }

        public DbSet<Sportiv> Sportivi { get; set; }
        public DbSet<Proba> Probe { get; set; }
    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    {
        protected override void Seed(DbCtx context)
        {
            Proba proba1 = new Proba
            {
                Denumire = "Patinaj artistic",
                Data = new System.DateTime(2018, 1, 13),
            };
            Proba proba2 = new Proba
            {
                Denumire = "Schi",
                Data = new System.DateTime(2018, 2, 1),
            };
            Proba proba3 = new Proba
            {
                Denumire = "Patinaj viteza",
                Data = new System.DateTime(2018, 1, 30),
            };
            context.Probe.Add(proba1);
            context.Probe.Add(proba2);
            context.Probe.Add(proba3);

            context.Sportivi.Add(new Sportiv
            {
                Nume = "Jobs",
                Prenume = "Scott",
                DataNasterii = new System.DateTime(1978, 6, 11),
                Tara = "Canada",
                IDProba = proba1.IDProba
            });
            context.Sportivi.Add(new Sportiv
            {
                Nume = "Virtue",
                Prenume = "Tessa",
                DataNasterii = new System.DateTime(1982, 9, 23),
                Tara = "Canada",
                IDProba = proba1.IDProba
            });
            context.Sportivi.Add(new Sportiv
            {
                Nume = "Marien",
                Prenume = "Helen",
                DataNasterii = new System.DateTime(1990, 1, 4),
                Tara = "China",
                IDProba = proba3.IDProba
            });
            context.SaveChanges();
            base.Seed(context);
        }
    }

}