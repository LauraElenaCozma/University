using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Books.Models
{
    public class Book
    {
        public int BookId { get; set; }
        public string Title { get; set; }
        public string Author { get; set; }
        public string Summary { get; set; }
        //one-to-many
        public int PublisherId { get; set; }   //relatia face ca cheia straina publisherId sa fie not null. int? si poate sa fie null
        public virtual Publisher Publisher { get; set; }

        //many-to-many
        public virtual ICollection<Genre> Genres { get; set; }
    }

    public class DbCtx : DbContext
    {
        public DbCtx() : base("BookCS")
        {
            // set the initializer here
            Database.SetInitializer<DbCtx>(new Initp());
            //Database.SetInitializer<DbCtx>(new CreateDatabaseIfNotExists<DbCtx>());
            //Database.SetInitializer<DbCtx>(new DropCreateDatabaseIfModelChanges<DbCtx>());
            //Database.SetInitializer<DbCtx>(new DropCreateDatabaseAlways<DbCtx>());
        }

        public DbSet<Book> Books { get; set; }
        public DbSet<Publisher> Publishers { get; set; }

        public DbSet<Genre> Genres { get; set; }

        public DbSet<ContactInfo> ContactInfos { get; set; }
    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    { // custom initializer
        protected override void Seed(DbCtx ctx)
        {
            ctx.Books.Add(new Book
            {
                Title = "The Atomic Times",
                Author = "Michael Harris",
                Summary = "The biggest and baddest of America’s atmospheric nuclear weapons test series, " +
                "Redwing mixed saber rattling with mad science, while overlooking its cataclysmic human, geopolitical and ecological effects." +
                "  But mostly, Redwing just messed with guys’ heads.",
                Publisher = new Publisher { Name = "Macmillan Publishers", ContactInfo = new ContactInfo { PhoneNumber = "0787294919" } },
                Genres = new List<Genre>
                {
                    new Genre {Name = "Satire"},
                    new Genre {Name = "Allegory"}
                }
            });
            ctx.Books.Add(new Book 
            { 
                Title = "In Defense of Elitism", 
                Author = "Joel Stein",
                Summary = "From Thurber finalist and former star Time columnist Joel Stein comes a " +
                "'brilliant exploration' (Walter Isaacson) of America's political culture war" +
                " and a hilarious call to arms for the elite.",
                Publisher = new Publisher { Name = "HarperCollins", ContactInfo = new ContactInfo { PhoneNumber = "0787294919" } },
                Genres = new List<Genre>
                {
                    new Genre {Name = "Fabilau"},
                    new Genre {Name = "Burlesque"}
                }
            });
            ctx.Books.Add(new Book 
            { 
                Title = "Data curenta", 
                Author = DateTime.Now.ToString(),
                Publisher = new Publisher { Name = "Scholastic", ContactInfo = new ContactInfo { PhoneNumber = "0713201002" } },
                
            });
            ctx.SaveChanges();
            base.Seed(ctx);
        }
    }
}