using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Books.Models
{
    public class BookType
    {
        public int BookTypeId { get; set; }
        public string Name { get; set; }

        //many-to-one
        public virtual IEnumerable<Book> Books { get; set; }
    }
}