using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Books_CRUD.Models
{
    public class Genre
    {
        public int GenreId { get; set; }
        public String Name { get; set; }
        public virtual ICollection<Book> Books { get; set; }
    }
}