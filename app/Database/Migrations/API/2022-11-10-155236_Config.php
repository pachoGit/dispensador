<?php

namespace App\Database\Migrations\API;

use CodeIgniter\Database\Migration;

class Config extends Migration
{
    public function up()
    {
        $this->forge->addField([
            'id_config' => [
                'type'           => 'INT',
                'constraint'     => 5,
                'unsigned'       => true,
                'auto_increment' => true
            ],
            'water_porc' => [
                'type'       => 'INT',
                'null'       => true
            ],
            'grain_porc' => [
                'type'       => 'INT',
                'null'       => true
            ],
            'description' => [
                'type'       => 'VARCHAR',
                'constraint' => '150',
                'null'       => true
            ],
            'created_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'updated_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'deleted_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],

        ]);
        $this->forge->addKey('id_config', true);
        $this->forge->createTable('config');
    }

    public function down()
    {
        $this->forge->dropTable('config');
    }
}
