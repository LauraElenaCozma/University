using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Books.MyValidator;

namespace Books.Models
{
    public class Book
    {
        public int BookId { get; set; }
        [MinLength(2, ErrorMessage = "Title cannot be less than 2"), 
            MaxLength(2000, ErrorMessage = "Title cannot be longer than 2000")]
        public string Title { get; set; }
        [MinLength(2, ErrorMessage = "Author name cannot be less than 2"),
            MaxLength(2000, ErrorMessage = "Author name cannot be longer than 2000")]
        public string Author { get; set; }
        [MinLength(2, ErrorMessage = "Summary cannot be less than 2"),
            MaxLength(2000, ErrorMessage = "Summary cannot be longer than 2000")]
        public string Summary { get; set; }

        [PrimeNumberValidator] 
        public int NoOfPages { get; set; }
        //one-to-many
        public int PublisherId { get; set; }   //relatia face ca cheia straina publisherId sa fie not null. int? si poate sa fie null
        public virtual Publisher Publisher { get; set; }

        //many-to-many
        public virtual ICollection<Genre> Genres { get; set; }

        //one-to-many
        public int BookTypeId { get; set; }

        [ForeignKey("BookTypeId")]
        public virtual BookType BookType { get; set; }

        /*
        //Rezolvare laborator

        public IEnumerable<SelectListItem> BookTypeList { get; set; }
        */


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

        public DbSet<BookType> BookTypes { get; set; }
    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    { // custom initializer
        protected override void Seed(DbCtx ctx)
        {
            BookType cover1 = new BookType { BookTypeId = 67, Name = "Hardcover" };
            BookType cover2 = new BookType { BookTypeId = 68, Name = "Paperback" };
            ctx.BookTypes.Add(cover1); 
            ctx.BookTypes.Add(cover2); 
            ctx.Books.Add(new Book
            {
                Title = "The Atomic Times",
                Author = "Michael Harris",
                Summary = "The biggest and baddest of America’s atmospheric nuclear weapons test series, " +
                "Redwing mixed saber rattling with mad science, while overlooking its cataclysmic human, geopolitical and ecological effects." +
                "  But mostly, Redwing just messed with guys’ heads.",
                Publisher = new Publisher { Name = "Macmillan Publishers", ContactInfo = new ContactInfo { PhoneNumber = "0787294919" } },
                BookTypeId = cover1.BookTypeId,
                NoOfPages = 79,
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
                BookTypeId = cover1.BookTypeId,
                NoOfPages = 13,
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
                BookTypeId = cover2.BookTypeId,
                NoOfPages = 11
            });
            ctx.SaveChanges();
            base.Seed(ctx);
        }
    }
}